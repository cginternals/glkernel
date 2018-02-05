#include <cppexpose/variant/Variant.h>

class KernelJsonImporter
{
public:
    explicit KernelJsonImporter(const std::string & inputFileName);
    cppexpose::Variant getKernel();

protected:
    cppexpose::Variant m_kernelVariant;
};
