#include "KernelGenerator.h"
#include "KernelObject.h"

#include "helper.h"
#include "JSInterface.h"

#include <glkernel/Kernel.h>
#include <glkernel/noise.h>
#include <glkernel/sort.h>
#include <glkernel/sequence.h>
#include <glkernel/shuffle.h>

#include <cppexpose/scripting/ScriptContext.h>
#include <cppassist/logging/logging.h>

#include <string>
#include <fstream>
#include <sstream>

KernelGenerator::KernelGenerator(const std::string& inputFileName)
{
    auto apiStream = std::ifstream{"data/glkernel.js"};
    throwIfNot(apiStream.is_open(), "glkernel.js could not found.");

    auto scriptStream = std::ifstream{inputFileName};
    throwIfNot(scriptStream.is_open(), "Input file " + inputFileName + " could not be found.");

    auto combinedStringStream = std::stringstream{};
    combinedStringStream << apiStream.rdbuf() << scriptStream.rdbuf();
    m_scriptCode = combinedStringStream.str();
}

cppexpose::Variant KernelGenerator::generateKernelFromJavascript()
{
    JSInterface jsInterface;

    cppexpose::ScriptContext scriptContext;
    scriptContext.addGlobalObject(&jsInterface);
    scriptContext.scriptException.connect([](const std::string & msg) {
        cppassist::error() << msg;
    });

    auto variant = scriptContext.evaluate(m_scriptCode);

    if (variant.hasType<cppexpose::Object*>())
    {
        auto kernelObject = variant.value<cppexpose::Object*>();

        auto kernel1Object = dynamic_cast<Kernel1Object*>(kernelObject);
        if (kernel1Object)
        {
            return cppexpose::Variant::fromValue(kernel1Object->kernel());
        }

        auto kernel2Object = dynamic_cast<Kernel2Object*>(kernelObject);
        if (kernel2Object)
        {
            return cppexpose::Variant::fromValue(kernel2Object->kernel());
        }

        auto kernel3Object = dynamic_cast<Kernel3Object*>(kernelObject);
        if (kernel3Object)
        {
            return cppexpose::Variant::fromValue(kernel3Object->kernel());
        }

        auto kernel4Object = dynamic_cast<Kernel4Object*>(kernelObject);
        if (kernel4Object)
        {
            return cppexpose::Variant::fromValue(kernel4Object->kernel());
        }
    }
    return variant;
}
