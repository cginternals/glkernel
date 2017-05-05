#include "variantConversion.h"
#include "parsing.h"

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
        return 1;
    }

    //auto kernel = glkernel::kernel3(3, 3, 3);

    //glkernel::noise::uniform(kernel, glm::vec3{ 0.f, 0.f, 0.f } , glm::vec3{ 1.f, 1.f, 1.f });

    cppexpose::Variant kernelJSON;

    if (kernelVariant.hasType<glkernel::kernel3>())
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
