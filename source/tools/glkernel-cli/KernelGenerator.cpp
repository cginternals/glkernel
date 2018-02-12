#include "KernelGenerator.h"

#include <glkernel/Kernel.h>
#include <glkernel/noise.h>
#include <glkernel/sort.h>
#include <glkernel/sequence.h>
#include <glkernel/shuffle.h>

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
    glkernel::sequence::uniform(generatedKernel, 0.f, 1.f);
    glkernel::shuffle::bayer(generatedKernel);
//    glkernel::sort::distance(generatedKernel, 0.0f);

    return cppexpose::Variant::fromValue(generatedKernel);
}
