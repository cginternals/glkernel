#include "AbstractKernelExporter.h"

#include <png.h>

class PngExporter : public AbstractKernelExporter
{
public:
    PngExporter(const cppexpose::Variant & kernel, const std::string & outFileName) :
        AbstractKernelExporter{kernel, outFileName} {}

    void exportKernel() override;

protected:
    template <typename T>
    png_doublep * toPng(const glkernel::tkernel<T> & kernel, const int channels);

    void writeToFile(png_doublep * data, const int colorType, const png_uint_32 height, const png_uint_32 width);
};