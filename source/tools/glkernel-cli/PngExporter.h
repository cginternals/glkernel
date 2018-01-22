#include "AbstractKernelExporter.h"

#include <png.h>

class PngExporter : public AbstractKernelExporter
{
public:
    PngExporter(const cppexpose::Variant & kernel, const std::string & outFileName) :
        AbstractKernelExporter{kernel, outFileName} {}

    void exportKernel() override;

protected:
    png_doublep * toPng(const cppexpose::Variant & kernelVariant);

    template <typename T>
    png_doublep * toPng(const glkernel::tkernel<T> & kernel, int channels, int colorType);

    void writeToFile(png_doublep * data);
};