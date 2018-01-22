#include "PngExporter.h"

#include <cppassist/logging/logging.h>

// http://www.labbookpages.co.uk/software/imgProc/libPNG.html

template <typename T>
void writeData(T cellValue, png_doublep outputRow, int x, int channels);

template <>
void writeData(float cellValue, png_doublep outputRow, int x, int channels)
{
    outputRow[x * channels] = static_cast<double>(cellValue);
}

template <>
void writeData(glm::vec2 cellValue, png_doublep outputRow, int x, int channels)
{
    outputRow[x * channels] = static_cast<double>(cellValue.x);
    outputRow[x * channels + 1] = static_cast<double>(cellValue.y);
}

template <>
void writeData(glm::vec3 cellValue, png_doublep outputRow, int x, int channels)
{
    outputRow[x * channels] = static_cast<double>(cellValue.x);
    outputRow[x * channels + 1] = static_cast<double>(cellValue.y);
    outputRow[x * channels + 2] = static_cast<double>(cellValue.z);
}

template <>
void writeData(glm::vec4 cellValue, png_doublep outputRow, int x, int channels)
{
    outputRow[x * channels] = static_cast<double>(cellValue.x);
    outputRow[x * channels + 1] = static_cast<double>(cellValue.y);
    outputRow[x * channels + 2] = static_cast<double>(cellValue.z);
    outputRow[x * channels + 3] = static_cast<double>(cellValue.w);
}

void PngExporter::exportKernel() {
    auto pngData = toPng(m_kernel);

    writeToFile(pngData);
}

png_doublep * PngExporter::toPng(const cppexpose::Variant & kernelVariant) {

    if (kernelVariant.hasType<glkernel::kernel4>())
    {
        return toPng(kernelVariant.value<glkernel::kernel4>(), 4, PNG_COLOR_TYPE_RGBA);
    }
    else if (kernelVariant.hasType<glkernel::kernel3>())
    {
        return toPng(kernelVariant.value<glkernel::kernel3>(), 3, PNG_COLOR_TYPE_RGB);
    }
    else if (kernelVariant.hasType<glkernel::kernel2>())
    {
        return toPng(kernelVariant.value<glkernel::kernel2>(), 2, PNG_COLOR_TYPE_GA);
    }
    else if (kernelVariant.hasType<glkernel::kernel1>())
    {
        return toPng(kernelVariant.value<glkernel::kernel1>(), 1, PNG_COLOR_TYPE_GRAY);
    }
    else
    {
        cppassist::error() << "Unknown kernel type found. Aborting...";
        return (png_doublep *) malloc(0); // TODO review
    }
}

// TODO 3D kernels (with depth)
template <typename T>
png_doublep * PngExporter::toPng(const glkernel::tkernel<T> & kernel, int channels, int colorType)
{
    // memory for all rows:
    auto data = (png_doublep *) malloc(kernel.height() * sizeof(png_doublep));
    // memory for one row: amount of channes * amount of pixels * png byte size
    for(int y = 0; y < kernel.height(); ++y) {
        data[y] = (png_doublep) malloc(channels * kernel.width() * sizeof(double));
    }

    for (auto y = 0; y < kernel.height(); ++y)
    {
        for (auto x = 0; x < kernel.width(); ++x)
        {
//            for (auto c = 0; c < channels; ++c)
//            {
//                data[y][x * channels + c] = ;
//            }
            writeData<T>(kernel.value(x, y, 0), data[y], x, channels);
//            auto val = kernel.value(x, y, 0);
//            data[y][x * channels] = val.x;
//            data[y][x * channels + 1] = val.y;
//            data[y][x * channels + 2] = val.z;
        }
    }

    return data;
}

// TODO free up pointers upon failure
void PngExporter::writeToFile(png_doublep * data) {
    /* create file */
    FILE *fp = fopen(m_outFileName.c_str(), "wb");
    if (!fp)
    {
        cppassist::error() << "File " << m_outFileName << " could not be opened for writing";
        return;
    }


    /* initialize stuff */
    auto png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if (!png_ptr)
    {
        cppassist::error() << "png_create_write_struct failed";
        return;
    }

    auto info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        cppassist::error() << "png_create_info_struct failed";
        return;
    }

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        cppassist::error() << "Error during init_io";
        return;
    }

    png_init_io(png_ptr, fp);


    /* write header */
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        cppassist::error() << "Error during writing header";
        return;
    }

    png_set_IHDR(png_ptr,
                 info_ptr,
                 100, // TODO kernel width
                 100, // TODO kernel height
                 16, // TODO bit depth
                 PNG_COLOR_TYPE_RGB, // TODO colorType
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr);


    /* write bytes */
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        cppassist::error() << "Error during writing bytes";
        return;
    }

    png_write_image(png_ptr, (png_bytepp) data);


    /* end write */
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        cppassist::error() << "Error during writing bytes";
        return;
    }

    png_write_end(png_ptr, nullptr);

    /* cleanup heap allocation */
    // TODO kernel height
    for (size_t y = 0; y < 100; ++y)
        free(data[y]);
    free(data);

    fclose(fp);

    png_destroy_write_struct(&png_ptr, &info_ptr);
}
