#include "KernelExporter.hpp"

class KernelJsonExporter : public KernelExporter {
protected:
public:
    KernelJsonExporter(const cppexpose::Variant & kernel, const std::string & outFileName) :
        KernelExporter{kernel, outFileName} {}

    void exportKernel() override;

protected:
    cppexpose::Variant toJsonArray(const cppexpose::Variant & kernelVariant);
    void writeToFile(const cppexpose::Variant & jsonArray);
    std::string stringify(const cppexpose::Variant & jsonArray);

    void appendFloatValues(cppexpose::VariantArray *kernelArray, float toAppend, ...);
    void appendDoubleValues(cppexpose::VariantArray *kernelArray, double toAppend, ...);
};
