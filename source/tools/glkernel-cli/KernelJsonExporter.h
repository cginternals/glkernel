#include "AbstractKernelExporter.h"

class KernelJsonExporter : public AbstractKernelExporter {
protected:
public:
    KernelJsonExporter(const cppexpose::Variant & kernel, const std::string & outFileName) :
        AbstractKernelExporter{kernel, outFileName} {}

    void exportKernel() override;

protected:
    cppexpose::Variant toJsonArray(const cppexpose::Variant & kernelVariant);

    template <typename T>
    cppexpose::Variant toJsonArray(const glkernel::tkernel<T> & kernel);

    template <typename T>
    cppexpose::Variant prepareResult(const glkernel::tkernel<T> &kernel);

    void writeToFile(const cppexpose::Variant & jsonArray);

    std::string stringify(const cppexpose::Variant & jsonArray);
};
