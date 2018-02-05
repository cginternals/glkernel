#include "PngExporter.h"

#include "helper.h"

#include <cppassist/logging/logging.h>

void PngExporter::exportKernel() {
    png_doublep * pngData;
    int colorType;
    png_uint_32 width;
    png_uint_32 height;
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

    // TODO multiply height and width widh depth for 3D kernels
    writeToFile(pngData, colorType, height, width);
}


// TODO 3D kernels (with depth)
template <typename T>
png_doublep * PngExporter::toPng(const glkernel::tkernel<T> & kernel, const int channels)
{
    const auto minMaxElements = findMinMaxElements(kernel);
    cppassist::info() << minMaxElements.first << ", " << minMaxElements.second;
    // memory for all rows:
    auto rows = (png_doublep *) malloc(kernel.height() * sizeof(png_doublep));
    // memory for one row: amount of channes * amount of pixels * png byte size
    for(int y = 0; y < kernel.height(); ++y) {
        rows[y] = (png_doublep) malloc(channels * kernel.width() * sizeof(double));
    }

    for (auto y = 0; y < kernel.height(); ++y)
    {
        for (auto x = 0; x < kernel.width(); ++x)
        {
            writeData<T>(kernel.value(x, y, 0), rows[y], x);
        }
    }

    return rows;
}


// http://www.labbookpages.co.uk/software/imgProc/libPNG.html
// TODO free up pointers upon failure
void PngExporter::writeToFile(png_doublep * data, const int colorType, const png_uint_32 height, const png_uint_32 width) {
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
                 width,
                 height,
                 16, // bit depth
                 colorType,
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
    for (size_t y = 0; y < height; ++y)
        free(data[y]);
    free(data);

    fclose(fp);

    png_destroy_write_struct(&png_ptr, &info_ptr);
}
