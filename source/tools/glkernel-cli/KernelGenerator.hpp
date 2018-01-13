#include <cppexpose/variant/Variant.h>

class KernelGenerator
{
public:
    explicit KernelGenerator(const std::string & inputFileName);
    cppexpose::Variant generateKernelFromJavascript();
protected:
    std::string m_scriptCode;
};