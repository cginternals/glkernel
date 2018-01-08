#include "KernelExporter.hpp"

class KernelJsonExporter : public KernelExporter {
protected:
public:
    KernelJsonExporter(const cppexpose::Variant & kernel, const std::string & outFileName) :
        KernelExporter{kernel, outFileName} {}

    void export() override;

protected:
    cppexpose::Variant toJsonArray(const cppexpose::Variant & kernel);
    void writeToFile(const cppexpose::Variant & jsonArray);
    std::string stringify(const cppexpose::Variant & jsonArray);
};
