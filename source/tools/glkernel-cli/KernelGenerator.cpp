#include "KernelGenerator.hpp"

#include <glkernel/Kernel.h>

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
    auto generatedKernel = glkernel::kernel4{}; // TODO generate from js scriptCode

    return cppexpose::Variant::fromValue(generatedKernel);
}
