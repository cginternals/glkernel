#include "KernelGeneration.h"
#include "KernelToJson.h"

#include <iostream>
#include <fstream>

#include <cppassist/cmdline/ArgumentParser.h>

#include <cppexpose/variant/Variant.h>
#include <cppexpose/json/JSON.h>

int main(int argc, char* argv[])
{
    cppassist::ArgumentParser argParser;
    argParser.parse(argc, argv);

    auto inFilename = argParser.value("--i");
    auto outFilename = argParser.value("--o");

    cppexpose::Variant kernelDescription;

    if (!generateKernelFromDescription(kernelDescription, inFilename))
    {
        std::cerr << "ERROR: kernel generation failed. Aborting..." << std::endl;
        return 1;
    }

    cppexpose::Variant kernelJSON;

    if (kernelDescription.hasType<glkernel::kernel4>())
    {
        kernelJSON = toJSON(kernelDescription.value<glkernel::kernel4>());
    }
    else if (kernelDescription.hasType<glkernel::kernel3>())
    {
        kernelJSON = toJSON(kernelDescription.value<glkernel::kernel3>());
    }
    else if (kernelDescription.hasType<glkernel::kernel2>())
    {
        kernelJSON = toJSON(kernelDescription.value<glkernel::kernel2>());
    }
    else if (kernelDescription.hasType<glkernel::kernel1>())
    {
        kernelJSON = toJSON(kernelDescription.value<glkernel::kernel1>());
    }

    std::ofstream outStream(outFilename);

    if (!outStream.is_open())
    {
        std::cerr << "ERROR: Output file could not be created. Aborting..." << std::endl;
        return 1;
    }

    outStream << cppexpose::JSON::stringify(kernelJSON, cppexpose::JSON::OutputMode::Beautify) << std::endl;
}
