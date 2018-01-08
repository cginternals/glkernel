#include <string>
#include <cppexpose/variant/Variant.h>

#include <glkernel/Kernel.h>

class KernelExporter {
public:
    KernelExporter(const cppexpose::Variant & kernelVariant, const std::string & outFileName, bool force) :
    m_kernel{kernelVariant}, m_outFileName{outFileName}, m_force{force} {}

    virtual void export() = 0;
protected:
    cppexpose::Variant m_kernel;
    std::string m_outFileName;
    bool m_force;
};