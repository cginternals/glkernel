
import posixpath # instead of os.path, to always use forward slashes
import os
import re

# TODOs:
# (more TODOs in code)

standardTypes = {
    "bool",
    "char",
    "short",
    "int",
    "long",
    "long long",
    "unsigned char",
    "unsigned short",
    "unsigned int",
    "unsigned long",
    "unsigned long long",
    "float",
    "double",
    "long double",

    "size_t",
    "glm::uint16"
}

# ------------
# large-scale parsing

def findPairedBrace(code):
    nl = 1

    for i,c in enumerate(code):
        if c == '}': nl -= 1
        if c == '{': nl += 1

        if nl == 0:
            return i

def getNamespaces(code):
    namespaces = dict()
    global namespaceBeginPattern
    namespaceBeginPattern = re.compile(r"^namespace(?:\s+(?P<name>\w+))?\s*\{", re.M | re.S)

    lastEnd = 0
    for match in namespaceBeginPattern.finditer(code):
        # skip inner namespaces
        if match.start() < lastEnd:
            continue

        nsStart = match.end()                             # behind opening brace
        nsEnd = findPairedBrace(code[nsStart:]) + nsStart # index of closing brace

        subNamespaces = getNamespaces(code[nsStart:nsEnd])
        namespaces[(nsStart,nsEnd)] = (match.group("name") or "<unnamed>", subNamespaces)

        # remember end for skipping inner namespaces
        lastEnd = nsEnd

    return namespaces

def namespaceAtPosition(namespaces, pos):
    for span in namespaces:
        if pos in range(*span):
            innerNS = namespaceAtPosition(namespaces[span][1], pos - span[0])

            return namespaces[span][0] + ("::" + innerNS if innerNS else "")

    return ""

# ------------
# small-scale parsing

def removeCVRef(typeString):
    return re.sub(r'^(?:const |volatile )*(.*?)(?:\s*&)?$', r'\1', typeString)

def splitParams(paramString):
    splitParams = [p.strip() for p in paramString.split(',') if p.strip()]

    i = 0
    while i < len(splitParams)-1:
        if splitParams[i].count('<') != splitParams[i].count('>'):
            splitParams[i:i+2] = [splitParams[i] + ", " + splitParams[i+1]]
        else:
            i += 1

    paramDefaults = [(split[0].strip(), split[1].strip() if len(split) > 1 else '') for split in [p.rsplit('=', 1) for p in splitParams]]
    paramsSplit = [(l.strip(), r.strip(), d) for l,r,d in [p.rsplit(' ', 1) + [d] for p,d in paramDefaults]]

    return paramsSplit

def removeParamDefaults(params):
    return [(p[0], p[1]) for p in params]

def getParamNames(params):
    return [p[1] for p in params]

def getParamTypes(params):
    return [p[0] for p in params]

def getParamDefaults(params):
    return [(p[1], p[2]) for p in params if p[2]]

def possibleTypes(argType, templateList):
    if re.match("^\w+$", argType): # argType is just single word, e.g. 'T'
        if "std::enable_if<std::is_floating_point<"+argType+">::value>::type" in templateList:
            return {"float"}
        else:
            return {"float", "vec2", "vec3", "vec4"}

    genVecMatch = re.match("(\w+)\s*<\s*\w+\s*,\s*\w+\s*>", argType) # general glm vector, e.g. 'V<T, P>'
    if genVecMatch:
        if re.search("template\s*<\s*(?:typename|class)\s*,\s*glm::precision\s*>\s*(?:typename|class)\s*" + genVecMatch.group(1), templateList):
            return {"vec2", "vec3", "vec4"}

    specVecMatch = re.match("glm::tvec(\d)<.*?>", argType) # specific glm vector, e.g. 'glm::tcev4<T, P>'
    if specVecMatch:
        return {"vec"+specVecMatch.group(1)}

    return {argType}

def paramTypeFromKernelTypes(kernelTypeString, paramTypeString, templateList, enums):
    if possibleTypes(paramTypeString, templateList) == {'float'}:
        return "float"

    strippedTypeString = removeCVRef(paramTypeString)

    if kernelTypeString == strippedTypeString: # e.g. 'V<T, P>' and 'const V<T, P>&'
        return "same"

    if strippedTypeString in kernelTypeString: # e.g. 'const T&' and 'V<T, P>'
        return "float"

    if strippedTypeString in [e["name"] for e in enums]:
        return strippedTypeString

    if strippedTypeString in standardTypes:
        return strippedTypeString

    print("Unknown Type encountered: " + paramTypeString)

def getEnumValues(valueDefString):
    definitions = [d.strip() for d in valueDefString.split(',')]
    values = []

    i = 0
    for d in definitions:
        if '=' in d:
            _, _, expr = d.partition('=')
            i = eval(expr, dict(values))

        values.append((d,i))
        i += 1

    return values

# ------------
# generation

def enumForJS(value, enums):
    if "::" not in value:
        return value

    enumDict = {enum["name"]: {valueName:value for valueName, value in enum["values"]} for enum in enums}

    enumName, _, valueName = value.partition("::")

    if enumName not in enumDict:
        # TODO: Warning?
        return value

    if valueName not in enumDict[enumName]:
        # TODO: Warning?
        return value

    return enumName + "." + valueName

def jsFuncName(func):
    name = func["name"]
    if "alternativeNumber" in func:
        name += str(func["alternativeNumber"])

    return "_".join(func["namespace"].split('::')[1:] + [name])

def jsFunction(func, enums):
    assert func["namespace"].startswith("glkernel::"), "function \""+func["name"]+"\" from outside glkernel namespace: " + func["namespace"]

    namespaceStack = func["namespace"].split("::")
    namespaceStack.pop(0) # ignore outmost namespace glkernel

    defaultChecks = '\n'.join(["                {name} = (typeof {name} !== 'undefined') ? {name} : {default};".format(name=name, default=enumForJS(default, enums)) for name, default in getParamDefaults(func["params"])])
    if defaultChecks:
        defaultChecks = "\n                // Defaults\n" + defaultChecks + "\n"

    paramString = ', '.join(getParamNames(func["params"]))
    paramStringKomma = "" if not paramString else ', ' + paramString

    firstLine = "            {name}: function({params}) {{".format(name = func["name"], params = paramString)
    finalCall = "                _glkernel.{generatedName}(that.kernel{paramsWithKomma});".format(generatedName = jsFuncName(func), paramsWithKomma = paramStringKomma)

    jsCode = """{firstLine}{defaultChecks}
{finalCall}
                return that;
            }}""".format(firstLine = firstLine, defaultChecks = defaultChecks, finalCall = finalCall)

    return jsCode

def buildJSNamespaces(funcs, enums):
    namespaces = dict()

    for func in funcs:
        if func["namespace"] not in namespaces:
            namespaces[func["namespace"]] = []

        namespaces[func["namespace"]].append(jsFunction(func, enums))

    nsCodes = []

    for ns, codes in sorted(namespaces.items()):
        name = ns[len("glkernel::"):]

        functionsCode = ",\n".join(codes)
        nsCode = "        this.{name} = {{\n{funcCodes}\n        }};".format(name = name, funcCodes = functionsCode)

        nsCodes.append(nsCode)

    return "\n".join(nsCodes)

def buildJSEnums(enums):
    enumCodes = []
    for enum in sorted(enums, key=lambda e: e["name"]):
        valueLines = []
        for name, value in enum["values"]:
            valueLines.append("    " + name + ": " + str(value))

        valuesCode = ',\n'.join(valueLines)
        enumCode = "{name} = {{\n{members}\n}};".format(name = enum["name"], members = valuesCode)
        enumCodes.append(enumCode)

    return "\n\n".join(enumCodes)

def buildCPPFunctionAdds(funcs):
    return '\n'.join(['    addFunction("{name}", this, &JSInterface::{name});'.format(name = jsFuncName(func)) for func in funcs])

def buildCPPFunctionForwardDecl(func, enums):
    enumNames = [enum["name"] for enum in enums]

    funcName = jsFuncName(func)

    # Deduce parameter types
    kernelTypes = possibleTypes(func["kernelType"], func["template"])
    paramTypes = [paramTypeFromKernelTypes(func["kernelType"], param[0], func["template"], enums) for param in func["params"]]
    cases = [(kernelType, [kernelType if param == "same" else param for param in paramTypes]) for kernelType in kernelTypes]

    if "alternatives" in func:
        for alt in func["alternatives"]:
            altKernelTypes = possibleTypes(alt["kernelType"], alt["template"])
            altParamTypes = [paramTypeFromKernelTypes(alt["kernelType"], param[0], alt["template"], enums) for param in alt["params"]]
            cases += [(kernelType, [kernelType if param == "same" else param for param in altParamTypes]) for kernelType in altKernelTypes]

    cases.sort()

    typesPerParam = [{case[1][i] for case in cases} for i in range(len(cases[0][1]))]
    variantNeeded = [len(types) > 1 for types in typesPerParam]
    enumParam = [list(types)[0] in enumNames for types in typesPerParam]

    paramTypes = ["cppexpose::Object*"] + ["const cppexpose::Variant&" if needVariant else "int" if isEnum else list(types)[0] for types, needVariant, isEnum in zip(typesPerParam, variantNeeded, enumParam)]
    paramNames = ["obj"] + [param[1] for param in func["params"]]
    paramList = ", ".join(type + " " + name for type,name in zip(paramTypes, paramNames))

    return "    void " + funcName + "(" + paramList + ");"

def buildCPPFunctionForwardDecls(funcs, enums):
    return '\n'.join([buildCPPFunctionForwardDecl(func, enums) for func in funcs])

def buildCPPIncludes(fileNames):
    includeFiles = []

    for f in fileNames:
        if not "include/" in f:
            print("Error: " + f + " is outside include directory!")
            continue

        while not f.startswith("include/"):
            f = f[1:]

        f = f[len("include/"):]
        includeFiles.append(f)

    return '\n'.join(['#include <' + name + '>' for name in includeFiles])

def buildCPPImplementation(func, enums):
    enumNames = [enum["name"] for enum in enums]

    funcName = jsFuncName(func)

    # Deduce parameter types
    kernelTypes = possibleTypes(func["kernelType"], func["template"])
    paramTypes = [paramTypeFromKernelTypes(func["kernelType"], param[0], func["template"], enums) for param in func["params"]]
    cases = [(kernelType, [kernelType if param == "same" else param for param in paramTypes]) for kernelType in kernelTypes]

    if "alternatives" in func:
        for alt in func["alternatives"]:
            altKernelTypes = possibleTypes(alt["kernelType"], alt["template"])
            altParamTypes = [paramTypeFromKernelTypes(alt["kernelType"], param[0], alt["template"], enums) for param in alt["params"]]
            cases += [(kernelType, [kernelType if param == "same" else param for param in altParamTypes]) for kernelType in altKernelTypes]

    cases.sort()

    typesPerParam = [{case[1][i] for case in cases} for i in range(len(cases[0][1]))]
    variantNeeded = [len(types) > 1 for types in typesPerParam]
    enumParam = [list(types)[0] in enumNames for types in typesPerParam]

    paramTypes = ["cppexpose::Object*"] + ["const cppexpose::Variant&" if needVariant else "int" if isEnum else list(types)[0] for types, needVariant, isEnum in zip(typesPerParam, variantNeeded, enumParam)]
    paramNames = ["obj"] + [param[1] for param in func["params"]]
    paramList = ", ".join(type + " " + name for type,name in zip(paramTypes, paramNames))

    # Parameters with only one possible type may be handled before branching into kernel types
    earlyConv = []
    for param, enumType in [(name, list(types)[0]) for name, types, isEnum in zip(paramNames[1:], typesPerParam, enumParam) if isEnum]:
        enum = [e for e in enums if e["name"] == enumType][0]
        earlyConv.append("    const auto {name}_enum = static_cast<{namespace}::{type}>({name});".format(name=param, type=enum["name"], namespace = enum["namespace"]))

    earlyConversions = '\n'.join(earlyConv)
    if earlyConversions:
        earlyConversions += '\n\n'

    # Split cases by kernel type
    casesByKernelType = dict()
    for kernel, params in cases:
        if kernel not in casesByKernelType:
            casesByKernelType[kernel] = []
        casesByKernelType[kernel].append(params)

    # Build code for different kernel types
    kernelCases = []
    for kernelType, cases in sorted(casesByKernelType.items()):
        kernelDim = 1 if kernelType == "float" else int(kernelType[-1])
        firstLine = "    if (auto kernelObj = dynamic_cast<Kernel" + str(kernelDim) + "Object*>(obj))"
        neededVariantChecks = False

        # Build code for specific parameter type constellations
        paramCases = []
        for case in cases:
            # Check if variants contain acceptable values
            variantChecks = []
            for name, type, needsVariant in zip(paramNames[1:], case, variantNeeded):
                if not needsVariant:
                    continue
                checkFunction = "canBe" + type[0].upper() + type[1:]
                variantChecks.append(checkFunction + "(" + name + ")")

                neededVariantChecks = True

            # Unpack variants to usable values
            variantUnpackers = []
            for name, type, needsVariant in zip(paramNames[1:], case, variantNeeded):
                if not needsVariant:
                    continue
                convFunction = "variantTo" + type[0].upper() + type[1:]
                variantUnpackers.append("        const auto {name}_conv = {func}({name});".format(name = name, func = convFunction))

            variantUnpackingCode = '\n'.join(variantUnpackers)
            if variantUnpackingCode:
                variantUnpackingCode += '\n\n'

            finalCallParams = ["kernelObj->kernel()"] + [name + ("_enum" if isEnum else "_conv" if needsVariant else "") for name, isEnum, needsVariant in zip(paramNames[1:], enumParam, variantNeeded)]
            finalCallParamString = ', '.join(finalCallParams)
            finalCallString = "        {namespace}::{name}({params});".format(namespace = func["namespace"], name = func["name"], params = finalCallParamString)

            innerCode = "{variants}{finalCall}\n        return;".format(variants = variantUnpackingCode, finalCall = finalCallString)

            caseCode = innerCode
            if variantChecks:
                variantCheckCode = ' && '.join(variantChecks)
                indentedInnerCode = '\n'.join([("    " + line).rstrip() for line in innerCode.split('\n')])
                caseCode = "        if ({varChecks})\n        {{\n{innerCode}\n        }}".format(varChecks = variantCheckCode, innerCode = indentedInnerCode)

            paramCases.append(caseCode)

        if neededVariantChecks:
            paramCases.append("        std::cerr << \"Invalid parameters for " + funcName + "\" << std::endl;\n        return;")

        paramCasesCode = '\n\n'.join(paramCases)

        kernelCaseCode = "{firstLine}\n    {{\n{cases}\n    }}".format(firstLine = firstLine, cases = paramCasesCode)
        kernelCases.append(kernelCaseCode)

    kernelCasesCode = '\n\n'.join(kernelCases)

    fullCode = """void JSInterface::{funcName}({paramList})
{{
{earlyConv}{cases}

    std::cerr << "Invalid kernel object for {funcName}" << std::endl;
}}""".format(funcName = funcName, paramList = paramList, earlyConv = earlyConversions, cases = kernelCasesCode)

    return fullCode

def buildCPPImplementations(funcs, enums):
    return '\n\n\n'.join([buildCPPImplementation(func, enums) for func in funcs])

# ------------
# misc

def dedupeFuncs(funcs):
    i = 1
    while i < len(funcs):
        currentFunc = funcs[i]
        for otherFunc in funcs[:i]:
            if otherFunc["namespace"] != currentFunc["namespace"]:
                continue
            if otherFunc["name"] != currentFunc["name"]:
                continue

            if getParamNames(otherFunc["params"]) == getParamNames(currentFunc["params"]):
                # identical in JS -> can be safely removed
                funcs.remove(currentFunc)
                i -= 1

                if "alternatives" not in otherFunc:
                    otherFunc["alternatives"] = []
                otherFunc["alternatives"].append(currentFunc)

                break

            if "renamedAlternatives" not in otherFunc:
                otherFunc["renamedAlternatives"] = 0

            otherFunc["renamedAlternatives"] += 1
            currentFunc["alternativeNumber"] = otherFunc["renamedAlternatives"]

            break

        i += 1

# ------------
# main

def main(args):
    glkernelIncludeDir = "../source/glkernel/include/glkernel"
    sourceFiles = [posixpath.join(glkernelIncludeDir, p) for p in os.listdir(glkernelIncludeDir) if p not in ["Kernel.h", "glm_compatability.h"] and p.endswith(".h")]

    funcPattern = re.compile(r"^template\s*<(?P<template>.*?)>$\s*^(?P<return>\w+)\s(?P<name>\w+)\(\s*tkernel<(?P<kernelType>.*?)>\s*&\s*\w+\s*(?P<params>(?:,.*?)*)\);$", re.M | re.S)
    enumPattern = re.compile(r"^enum(?:\s+class)?\s+(?P<name>\w+)\s*(?::.*?\s*)?\{(?P<content>.*?)\};$", re.M | re.S)

    allFunctions = []
    allEnums = []
    for f in sourceFiles:
        content = ''
        with open(f,'r') as file:
            content = file.read()

        namespaces = getNamespaces(content)
        functionMatches = [m for m in funcPattern.finditer(content)]
        functions = [{
                        "name": f.group("name"),
                        "kernelType": f.group("kernelType"),
                        "namespace": namespaceAtPosition(namespaces, f.start()),
                        "params": splitParams(f.group("params")),
                        "return": f.group("return"),
                        "template": f.group("template")
                    } for f in functionMatches]

        enumMatches = [m for m in enumPattern.finditer(content)]
        enums = [{
                    "name": e.group("name"),
                    "values": getEnumValues(e.group("content")),
                    "namespace": namespaceAtPosition(namespaces, e.start())
                } for e in enumMatches]

        allFunctions.extend(functions)
        allEnums.extend(enums)

    dedupeFuncs(allFunctions)

    funcsJSCode = buildJSNamespaces(allFunctions, allEnums)
    enumJSCode = buildJSEnums(allEnums)

    templateDir = args.inDir
    cppDestDir = args.cppDir
    jsDestDir = args.jsDir

    with open(templateDir + "/glkernel.js.template", "r") as templateFile:
        with open(jsDestDir + "/glkernel.js", "w") as outFile:
            outFile.write(templateFile.read().format(enums=enumJSCode, functions=funcsJSCode))

    forwardDecls = buildCPPFunctionForwardDecls(allFunctions, allEnums)

    with open(templateDir + "/JSInterface.h.template", "r") as templateFile:
        with open(cppDestDir + "/JSInterface.h", "w") as outFile:
            outFile.write(templateFile.read().format(functionForwardDecls=forwardDecls))

    includes = buildCPPIncludes(sourceFiles)
    funcAdds = buildCPPFunctionAdds(allFunctions)
    funcImpl = buildCPPImplementations(allFunctions, allEnums)

    with open(templateDir + "/JSInterface.cpp.template", "r") as templateFile:
        with open(cppDestDir + "/JSInterface.cpp", "w") as outFile:
            outFile.write(templateFile.read().format(includes=includes, addFunctionCalls=funcAdds, generatedFunctions=funcImpl))

if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()

    parser.add_argument("--templates", "-t", metavar="<dir>", type=str, default=".", dest="inDir",  help="directory containing template files")
    parser.add_argument("--cpp-dest" , "-c", metavar="<dir>", type=str, default=".", dest="cppDir", help="directory where result .h and .cpp files are written to")
    parser.add_argument("--js-dest"  , "-j", metavar="<dir>", type=str, default=".", dest="jsDir",  help="directory where result .js files are written to")

    args = parser.parse_args()

    main(args)
