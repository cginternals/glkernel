#pragma once

#include <cppexpose/variant/Variant.h>

class JsonImporter
{
public:
    explicit JsonImporter(const std::string & inputFileName);
    cppexpose::Variant getKernel();

protected:
    cppexpose::Variant m_kernelVariant;
};
