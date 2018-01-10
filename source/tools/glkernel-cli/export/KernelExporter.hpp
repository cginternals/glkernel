#pragma once

#include <string>
#include <cppexpose/variant/Variant.h>

#include <glkernel/Kernel.h>

class KernelExporter
{
public:
    KernelExporter(const cppexpose::Variant & kernelVariant, const std::string & outFileName) :
    m_kernel{kernelVariant}, m_outFileName{outFileName} {}

    virtual void exportKernel() = 0;
protected:
    cppexpose::Variant m_kernel;
    std::string m_outFileName;
};