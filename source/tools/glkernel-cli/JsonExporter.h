#pragma once

#include "AbstractKernelExporter.h"

class JsonExporter : public AbstractKernelExporter {
public:
    JsonExporter(const cppexpose::Variant & kernel, const std::string & outFileName, const bool beautify) :
        AbstractKernelExporter{kernel, outFileName}, m_beautify{beautify} {}

    void exportKernel() override;

protected:
    cppexpose::Variant toJsonArray(const cppexpose::Variant & kernelVariant);

    template <typename T>
    cppexpose::Variant toJsonArray(const glkernel::tkernel<T> & kernel);

    template <typename T>
    cppexpose::Variant prepareResult(const glkernel::tkernel<T> &kernel);

    void writeToFile(const cppexpose::Variant & jsonArray);

    std::string stringify(const cppexpose::Variant & jsonArray);

    bool m_beautify;
};
