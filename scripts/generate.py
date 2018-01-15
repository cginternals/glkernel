from pathlib import Path
import re

# TODOs:
# (more TODOs in code)

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
        namespaces[range(nsStart,nsEnd)] = (match["name"] or "<unnamed>", subNamespaces)

        # remember end for skipping inner namespaces
        lastEnd = nsEnd

    return namespaces

def namespaceAtPosition(namespaces, pos):
    for span in namespaces:
        if pos in span:
            innerNS = namespaceAtPosition(namespaces[span][1], pos - span.start)

            return namespaces[span][0] + ("::" + innerNS if innerNS else "")

    return ""

# ------------
# small-scale parsing

def splitParams(paramString):
    splitParams = [p.strip() for p in paramString.split(',') if p.strip()]
    
    i = 0
    while i < len(splitParams)-1:
        if splitParams[i].count('<') != splitParams[i].count('>'):
            splitParams[i:i+2] = [splitParams[i] + "," + splitParams[i+1]]
        else:
            i += 1
    
    paramDefaults = [(split[0].strip(), split[1].strip() if len(split) > 1 else '') for split in [p.rsplit('=', 1) for p in splitParams]]
    paramsSplit = [(l.strip(), r.strip(), d) for l,r,d in [p.rsplit(' ', 1) + [d] for p,d in paramDefaults]]
    
    # Debug
    while False:
        cmd = input('>>>')
        if not cmd: break
        print(eval(cmd))
    
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
    # currently unused
    if re.match("^\w+$", argType):
        if "std::enable_if<std::is_floating_point<"+argType+">::value>::type" in templateList:
            return {"vec1"}
        else:
            return {"vec1", "vec2", "vec3", "vec4"}

    genVecMatch = re.match("(\w+)\s*<\s*\w+\s*,\s*\w+\s*>", argType)
    if genVecMatch:
        if re.search("template\s*<\s*(?:typename|class)\s*,\s*glm::precision\s*>\s*(?:typename|class)\s*" + genVecMatch[1], templateList):
            return {"vec2", "vec3", "vec4"}

    specVecMatch = re.match("glm::tvec(\d)<.*?>", argType)
    if specVecMatch:
        return {"vec"+specVecMatch[1]}

    return argType

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
    
    # TODO: Prefix of enum object
    return enumName + "." + valueName

def jsFunction(func, enums):
    assert func["namespace"].startswith("glkernel::"), "function \""+func["name"]+"\" from outside glkernel namespace: " + func["namespace"]
    
    namespaceStack = func["namespace"].split("::")
    namespaceStack.pop(0) # ignore outmost namespace glkernel
    
#    argCleans = '\n'.join(["            {name} = cleanArg({name});".format(name=name) for name in getParamNames(func["params"])])
#    if argCleans:
#        argCleans = "\n            // Clean arguments\n" + argCleans + "\n"
    
    defaultChecks = '\n'.join(["                {name} = (typeof {name} !== 'undefined') ? {name} : {default};".format(name=name, default=enumForJS(default, enums)) for name, default in getParamDefaults(func["params"])])
    if defaultChecks:
        defaultChecks = "\n                // Defaults\n" + defaultChecks + "\n"
    
    jsCode = """            {name}: function({params}) {{{defaultChecks}
                _glkernel.{generatedName}(that.kernel{paramsWithKomma});
                return that;
            }}""".format(
        name = func["name"],
        params = ', '.join(getParamNames(func["params"])),
        paramsWithKomma = ''.join([', ' + p for p in getParamNames(func["params"])]),
        generatedName = "_".join(namespaceStack + [func["name"]]),
#        argCleans = argCleans,
        defaultChecks = defaultChecks
    )
    
    return jsCode

def buildJSNamespaces(funcs, enums):
    namespaces = dict()
    
    for func in funcs:
        if func["namespace"] not in namespaces:
            namespaces[func["namespace"]] = []
        
        namespaces[func["namespace"]].append(jsFunction(func, enums))
    
    nsCodes = []
    
    for ns, codes in namespaces.items():
        name = ns[len("glkernel::"):]
        
        nsCodes.append(
        """        this.{name} = {{
{funcCodes}
        }};""".format(
                name = name,
                funcCodes = ",\n".join(codes)
            )
        )
    
    return "\n".join(nsCodes)

def buildJSEnums(enums):
    return "\n".join([
        """{name} = {{
{members}
}};""".format(
            name = enum["name"],
            members = ",\n".join(["    {name}: {value}".format(name=name, value=value) for name, value in enum["values"]])
        ) for enum in enums
    ])

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
            
            print("Warning: Method \"" + currentFunc["namespace"] + "::" + currentFunc["name"] + "\" has overloads that can not be trivially resolved!")

            # Debug
            while False:
                cmd = input('>>>')
                if not cmd: break
                print(eval(cmd))
            
        i += 1

# ------------
# main

def main():
    glkernelIncludeDir = Path("../source/glkernel/include/glkernel")
    sourceFiles = [str(p) for p in glkernelIncludeDir.glob("*.h") if p.name not in ["Kernel.h", "glm_compatability.h"]]

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
                        "name": f["name"],
                        "kernelType": f["kernelType"],
                        "namespace": namespaceAtPosition(namespaces, f.start()),
                        "params": splitParams(f["params"]),
                        "return": f["return"],
                        "template": f["template"]
                    } for f in functionMatches]
        
        enumMatches = [m for m in enumPattern.finditer(content)]
        enums = [{
                    "name": e["name"],
                    "values": getEnumValues(e["content"]),
                    "namespace": namespaceAtPosition(namespaces, e.start())
                } for e in enumMatches]

        allFunctions.extend(functions)
        allEnums.extend(enums)
    
    dedupeFuncs(allFunctions)
    
    funcsJSCode = buildJSNamespaces(allFunctions, allEnums)
    enumJSCode = buildJSEnums(allEnums)
    
    with open("glkernel.js.template", "r") as templateFile:
        with open("glkernel.js", "w") as outFile:
            outFile.write(templateFile.read().format(enums=enumJSCode, functions=funcsJSCode))
    
    # Debug
    while False:
        cmd = input('>>>')
        if not cmd: break
        print(eval(cmd))

if __name__ == "__main__":
    main()