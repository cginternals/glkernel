#pragma once

#include <glkernel/Kernel.h>

#include <cppexpose/variant/Variant.h>

namespace
{
    template <typename T>
    void appendValueToVariantArray(cppexpose::Variant & variant, const T & t);

    template <>
    void appendValueToVariantArray<float>(cppexpose::Variant & variant, const float & t)
    {
        variant.asArray()->push_back(t);
    }

    template <>
    void appendValueToVariantArray<glm::vec2>(cppexpose::Variant & variant, const glm::vec2 & t)
    {
        variant.asArray()->push_back(t.x);
        variant.asArray()->push_back(t.y);
    }

    template <>
    void appendValueToVariantArray<glm::vec3>(cppexpose::Variant & variant, const glm::vec3 & t)
    {
        variant.asArray()->push_back(t.x);
        variant.asArray()->push_back(t.y);
        variant.asArray()->push_back(t.z);
    }

    template <>
    void appendValueToVariantArray<glm::vec4>(cppexpose::Variant & variant, const glm::vec4 & t)
    {
        variant.asArray()->push_back(t.x);
        variant.asArray()->push_back(t.y);
        variant.asArray()->push_back(t.z);
        variant.asArray()->push_back(t.w);
    }
}

template <typename T>
cppexpose::Variant toJSON(const glkernel::tkernel<T> & kernel)
{
    cppexpose::Variant zArray = cppexpose::Variant::array();

    for (int z = 0; z < kernel.depth(); ++z)
    {
        cppexpose::Variant yArray = cppexpose::Variant::array();

        for (int y = 0; y < kernel.height(); ++y)
        {
            cppexpose::Variant xArray = cppexpose::Variant::array();

            for (int x = 0; x < kernel.width(); ++x)
            {
                cppexpose::Variant elementArray = cppexpose::Variant::array();

                const T& value = kernel.value(x, y, z);

                appendValueToVariantArray(elementArray, value);

                xArray.asArray()->push_back(elementArray);
            }

            yArray.asArray()->push_back(xArray);
        }

        zArray.asArray()->push_back(yArray);
    }

    cppexpose::Variant result = cppexpose::Variant::map();
    cppexpose::Variant size = cppexpose::Variant::map();

    size.asMap()->emplace("height", kernel.height());
    size.asMap()->emplace("width", kernel.width());
    size.asMap()->emplace("depth", kernel.depth());

    result.asMap()->emplace("size", size);
    result.asMap()->emplace("kernel", zArray);
    
    return result;
}
