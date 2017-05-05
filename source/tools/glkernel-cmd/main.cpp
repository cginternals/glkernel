#include "variantConversion.h"
#include "parsing.h"

#include <iostream>
#include <fstream>

#include <cppassist/cmdline/ArgumentParser.h>

#include <cppexpose/variant/Variant.h>
#include <cppexpose/json/JSON.h>
#include <cppassist/cmdline/ArgumentParser.h>

#include <glkernel/Kernel.h>
#include <glkernel/noise.h>

int main(int argc, char* argv[])
{
    cppassist::ArgumentParser argParser;
    argParser.parse(argc, argv);

    auto inFilename = argParser.value("--i");
    auto outFilename = argParser.value("--o");

    cppexpose::Variant kernelVariant;

    if (!generateKernelFromJSON(kernelVariant, inFilename))
    {
        std::cout << "Could not generate kernel. Possibly the input specification could not be parsed." << std::endl;
        return 1;
    }

    cppexpose::Variant kernelJSON;

    if (kernelVariant.hasType<glkernel::kernel4>())
    {
        kernelJSON = toJSON(kernelVariant.value<glkernel::kernel4>());
    }
    else if (kernelVariant.hasType<glkernel::kernel3>())
    {
        kernelJSON = toJSON(kernelVariant.value<glkernel::kernel3>());
    }
    else if (kernelVariant.hasType<glkernel::kernel2>())
    {
        kernelJSON = toJSON(kernelVariant.value<glkernel::kernel2>());
    }
    else if (kernelVariant.hasType<glkernel::kernel1>())
    {
        kernelJSON = toJSON(kernelVariant.value<glkernel::kernel1>());
    }

    std::ofstream outStream(outFilename);

    outStream << cppexpose::JSON::stringify(kernelJSON, cppexpose::JSON::OutputMode::Beautify) << std::endl;
}
