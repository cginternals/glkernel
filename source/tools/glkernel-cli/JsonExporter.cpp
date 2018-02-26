#include "JsonExporter.h"

#include <cppassist/logging/logging.h>

#include <iostream>
#include <fstream>
#include <algorithm>

void appendCell(cppexpose::VariantArray *kernelArray, std::initializer_list<float> cell)
{
    auto componentArrayVariant = cppexpose::Variant::array();
    auto componentArray = componentArrayVariant.asArray();
    componentArray->insert(componentArray->end(), cell.begin(), cell.end());
    kernelArray->push_back(componentArrayVariant);
}

template <typename T>
void appendCell(cppexpose::VariantArray * widthArray, const T & cell);

template <>
void appendCell<glm::vec4>(cppexpose::VariantArray * widthArray, const glm::vec4 & cell)
{
    appendCell(widthArray, {cell.x, cell.y, cell.z, cell.w});
}

template <>
void appendCell<glm::vec3>(cppexpose::VariantArray * widthArray, const glm::vec3 & cell)
{
    appendCell(widthArray, {cell.x, cell.y, cell.z});
}

template <>
void appendCell<glm::vec2>(cppexpose::VariantArray * widthArray, const glm::vec2 & cell)
{
    appendCell(widthArray, {cell.x, cell.y});
}

template <>
void appendCell<float>(cppexpose::VariantArray * widthArray, const float & cell)
{
    widthArray->push_back(cell);
}


void JsonExporter::exportKernel() {
    const auto jsonArray = toJsonArray(m_kernel);

    writeToFile(jsonArray);
}

cppexpose::Variant JsonExporter::toJsonArray(const cppexpose::Variant & kernelVariant)
{

    if (kernelVariant.hasType<glkernel::kernel4>())
    {
        return toJsonArray(kernelVariant.value<glkernel::kernel4>());
    }
    else if (kernelVariant.hasType<glkernel::kernel3>())
    {
        return toJsonArray(kernelVariant.value<glkernel::kernel3>());
    }
    else if (kernelVariant.hasType<glkernel::kernel2>())
    {
        return toJsonArray(kernelVariant.value<glkernel::kernel2>());
    }
    else if (kernelVariant.hasType<glkernel::kernel1>())
    {
        return toJsonArray(kernelVariant.value<glkernel::kernel1>());
    }
    else
    {
        cppassist::error() << "Unknown kernel type found. Aborting...";
        return cppexpose::Variant::fromValue(glkernel::kernel1{ });
    }
}

template <typename T>
cppexpose::Variant JsonExporter::toJsonArray(const glkernel::tkernel<T> & kernel)
{
    auto kernelArray = cppexpose::Variant::array();

    for (auto z = 0; z < kernel.depth(); ++z)
    {
        auto heightArray = cppexpose::Variant::array();

        for (auto y = 0; y < kernel.height(); ++y)
        {
            auto widthArray = cppexpose::Variant::array();

            for (auto x = 0; x < kernel.width(); ++x)
            {
                const T& cell = kernel.value(x, y, z);
                appendCell(widthArray.asArray(), cell);
            }
            heightArray.asArray()->push_back(widthArray);
        }
        kernelArray.asArray()->push_back(heightArray);
    }


    auto result = prepareResult(kernel);
    result.asMap()->emplace("kernel", kernelArray);

    return result;
}


template <typename T>
cppexpose::Variant JsonExporter::prepareResult(const glkernel::tkernel<T> & kernel)
{
    cppexpose::Variant result = cppexpose::Variant::map();
    cppexpose::Variant size = cppexpose::Variant::map();

    size.asMap()->emplace("width", kernel.width());
    size.asMap()->emplace("height", kernel.height());
    size.asMap()->emplace("depth", kernel.depth());

    result.asMap()->emplace("size", size);

    return result;
}


void JsonExporter::writeToFile(const cppexpose::Variant & jsonArray)
{
    std::ofstream outStream(m_outFileName);

    if (!outStream.is_open())
    {
        cppassist::error() << "Output file could not be created. Aborting...";
        return;
    }

    outStream << stringify(jsonArray) << std::endl;
}


std::string JsonExporter::stringify(const cppexpose::Variant &array)
{
    const auto outputMode = m_beautify
                          ? cppexpose::JSON::OutputMode::Beautify
                          : cppexpose::JSON::OutputMode::Compact;

    return cppexpose::JSON::stringify(array, outputMode);
}
