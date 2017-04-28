#include "variantConversion.h"

#include <fstream>

#include <cppexpose/json/JSON.h>
#include <cppassist/cmdline/ArgumentParser.h>

#include <glkernel/Kernel.h>
#include <glkernel/noise.h>

int main()
{
    auto kernel = glkernel::kernel3(3, 3, 3);

    glkernel::noise::uniform(kernel, glm::vec3{ 0.f, 0.f, 0.f } , glm::vec3{ 1.f, 1.f, 1.f });

    auto kernelVariant = toVariant(kernel);

    std::ofstream outStream("kernel.json");

    outStream << cppexpose::JSON::stringify(kernelVariant, cppexpose::JSON::OutputMode::Beautify) << std::endl;
}
