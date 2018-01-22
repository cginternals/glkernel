#include "KernelGenerator.h"

#include <glkernel/Kernel.h>
#include <glkernel/noise.h>
#include <glkernel/sort.h>

#include <string>
#include <fstream>
#include <sstream>

KernelGenerator::KernelGenerator(const std::string& inputFileName)
{
    auto inputStream = std::ifstream{inputFileName};
    auto inputStringStream = std::stringstream{};
    inputStringStream << inputStream.rdbuf();
    m_scriptCode = inputStringStream.str();
}

cppexpose::Variant KernelGenerator::generateKernelFromJavascript()
{
    // TODO generate from js scriptCode

    auto generatedKernel = glkernel::kernel3{ 100, 100, 1 };
    glkernel::noise::uniform(generatedKernel, 0.f, 1.f);

    return cppexpose::Variant::fromValue(generatedKernel);
}
