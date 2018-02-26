#include "PngExporter.h"

#include "helper.h"

#include <cppassist/logging/logging.h>

/*
 * bit depth 16: we need 2 bytes per cell value
 */
void writeData(float cellValue, png_bytep outputRow, int x)
{
    png_save_uint_16(outputRow + 2 * x, static_cast<uint16_t>(cellValue));
}

void writeData(glm::vec2 cellValue, png_bytep outputRow, int x)
{
    const auto offset = 4 * x;
    png_save_uint_16(outputRow + offset, static_cast<uint16_t>(cellValue.x));
    png_save_uint_16(outputRow + offset + 2, static_cast<uint16_t>(cellValue.y));
}

void writeData(glm::vec3 cellValue, png_bytep outputRow, int x)
{
    const auto offset = 6 * x;
    png_save_uint_16(outputRow + offset, static_cast<uint16_t>(cellValue.x));
    png_save_uint_16(outputRow + offset + 2, static_cast<uint16_t>(cellValue.y));
    png_save_uint_16(outputRow + offset + 4, static_cast<uint16_t>(cellValue.z));
}

void writeData(glm::vec4 cellValue, png_bytep outputRow, int x)
{
    const auto offset = 8 * x;
    png_save_uint_16(outputRow + offset, static_cast<uint16_t>(cellValue.x));
    png_save_uint_16(outputRow + offset + 2, static_cast<uint16_t>(cellValue.y));
    png_save_uint_16(outputRow + offset + 4, static_cast<uint16_t>(cellValue.z));
    png_save_uint_16(outputRow + offset + 6, static_cast<uint16_t>(cellValue.w));
}

void PngExporter::exportKernel()
{
    png_bytepp pngData = nullptr;
    int colorType = -1;
    png_uint_32 width = 0;
    png_uint_32 height = 0;

    if (m_kernel.hasType<glkernel::kernel4>())
    {
        colorType = PNG_COLOR_TYPE_RGBA;
        const auto kernel = m_kernel.value<glkernel::kernel4>();
        width = kernel.width();
        height = kernel.height();
        pngData = toPng(kernel, 4);
    }
    else if (m_kernel.hasType<glkernel::kernel3>())
    {
        colorType = PNG_COLOR_TYPE_RGB;
        const auto kernel = m_kernel.value<glkernel::kernel3>();
        width = kernel.width();
        height = kernel.height();
        pngData = toPng(kernel, 3);
    }
    else if (m_kernel.hasType<glkernel::kernel2>())
    {
        colorType = PNG_COLOR_TYPE_GA;
        const auto kernel = m_kernel.value<glkernel::kernel2>();
        width = kernel.width();
        height = kernel.height();
        pngData = toPng(kernel, 2);
    }
    else if (m_kernel.hasType<glkernel::kernel1>())
    {
        colorType = PNG_COLOR_TYPE_GRAY;
        const auto kernel = m_kernel.value<glkernel::kernel1>();
        width = kernel.width();
        height = kernel.height();
        pngData = toPng(kernel, 1);
    }
    else
    {
        cppassist::error() << "Unknown kernel type found. Aborting...";
        return;
    }

    // TODO multiply height and width with depth for 3D kernels
    writeToFile(pngData, colorType, height, width);
}


// TODO support 3D kernels with depth
// https://github.com/p-otto/glkernel/issues/44
template <typename T>
png_bytepp PngExporter::toPng(const glkernel::tkernel<T> & kernel, const int channels)
{
    const auto minmax = findMinMaxElements(kernel);
    const auto min = minmax.first;
    const auto max = minmax.second;

    // TODO calculate scaling factor, error rate, variance, stddeviation
    // https://github.com/p-otto/glkernel/issues/47
    cppassist::info() << "Scaling floating point range [" << min << ", " << max << "] to integer range [0, 65535]";

    // memory for all rows:
    auto rows = (png_bytepp) malloc(kernel.height() * sizeof(png_bytep));
    // memory for one row: amount of channes * amount of pixels * png byte size
    for(int y = 0; y < kernel.height(); ++y) {
        // we are using 16 bit depth, so we need 2 bytes per channel
        rows[y] = (png_bytep) malloc(channels * kernel.width() * 2 * sizeof(png_byte));
    }

    const auto range = max - min;

    for (auto y = 0; y < kernel.height(); ++y)
    {
        for (auto x = 0; x < kernel.width(); ++x)
        {
            auto value = kernel.value(x, y, 0);
            auto normalizedValue = (value - min) / range;
            auto scaledValue = normalizedValue * static_cast<float>(std::numeric_limits<uint16_t>::max());
            auto roundedValue = glm::round(scaledValue);

            writeData(roundedValue, rows[y], x);
        }
    }

    return rows;
}


// mostly taken from http://www.labbookpages.co.uk/software/imgProc/libPNG.html
void PngExporter::writeToFile(png_bytepp data, const int colorType, const png_uint_32 height, const png_uint_32 width)
{

    png_structp pngPtr = nullptr;
    png_infop infoPtr = nullptr;

    // create file
    FILE *pngOutputFile = fopen(m_outFileName.c_str(), "wb");

    if (!pngOutputFile)
    {
        cppassist::error() << "File " << m_outFileName << " could not be opened for writing";
        goto cleanup;
    }


    // initialize write structure
    pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!pngPtr)
    {
        cppassist::error() << "png_create_write_struct failed";
        goto cleanup;
    }

    // initialize info structure
    infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr)
    {
        cppassist::error() << "png_create_info_struct failed";
        goto cleanup;
    }

    // setjmp sets jump point to jump back to upon exception
    // this allows to find out where the exception occurred, print a corresponding error message, and clean up
    if (setjmp(png_jmpbuf(pngPtr)))
    {
        cppassist::error() << "Error during init_io";
        goto cleanup;
    }

    png_init_io(pngPtr, pngOutputFile);

    if (setjmp(png_jmpbuf(pngPtr)))
    {
        cppassist::error() << "Error during writing header";
        goto cleanup;
    }

    // write png header
    png_set_IHDR(pngPtr,
                 infoPtr,
                 width,
                 height,
                 16, // bit depth
                 colorType,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    png_write_info(pngPtr, infoPtr);

    if (setjmp(png_jmpbuf(pngPtr)))
    {
        cppassist::error() << "Error during writing bytes";
        return;
    }

    // write png data
    png_write_image(pngPtr, (png_bytepp) data);

    if (setjmp(png_jmpbuf(pngPtr)))
    {
        cppassist::error() << "Error during writing bytes";
        return;
    }

    png_write_end(pngPtr, nullptr);

    cleanup:

    if (pngOutputFile) fclose(pngOutputFile);
    if (infoPtr) png_free_data(pngPtr, infoPtr, PNG_FREE_ALL, -1);
    if (pngPtr) png_destroy_write_struct(&pngPtr, (png_infopp) nullptr);

    for (size_t y = 0; y < height; ++y)
        free(data[y]);
    free(data);
}
