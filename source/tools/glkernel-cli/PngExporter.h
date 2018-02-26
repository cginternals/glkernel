#pragma once

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
    png_bytepp toPng(const glkernel::tkernel<T> & kernel, int channels);

    void writeToFile(png_bytepp data, int colorType, png_uint_32 height, png_uint_32 width);
};
