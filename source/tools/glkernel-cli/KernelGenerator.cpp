#include "KernelGenerator.hpp"

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

    auto generatedKernel = glkernel::kernel2{ 3, 4, 5 };
    glkernel::noise::uniform(generatedKernel, 0.f, 1.f);
    glkernel::sort::distance(generatedKernel, {0.0f, 0.0f});

    return cppexpose::Variant::fromValue(generatedKernel);
}
