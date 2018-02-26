#include "helper.h"

#include <algorithm>
#include <vector>

#include <glkernel/Kernel.h>

void throwIfNot(bool condition, const std::string& msg)
{
    if (!condition)
    {
        throw std::logic_error(msg);
    }
}

std::pair<float, float> findMinMaxElements(const glkernel::tkernel<float> & kernel)
{
    const auto minmax = std::minmax_element(kernel.cbegin(), kernel.cend());
    return std::make_pair(*minmax.first, *minmax.second);
}

std::pair<float, float> findMinMaxElements(const glkernel::tkernel<glm::vec2> & kernel)
{
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::min();

    for (const auto & element : kernel)
    {
        const auto x = element.x;
        const auto y = element.y;

        min = x < min ? x : min;
        min = y < min ? y : min;

        max = x > max ? x : max;
        max = y > max ? y : max;
    }

    return std::make_pair(min, max);
}

std::pair<float, float> findMinMaxElements(const glkernel::tkernel<glm::vec3> & kernel)
{
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::min();

    for (const auto & element : kernel)
    {
        const auto x = element.x;
        const auto y = element.y;
        const auto z = element.z;

        min = x < min ? x : min;
        min = y < min ? y : min;
        min = z < min ? z : min;

        max = x > max ? x : max;
        max = y > max ? y : max;
        max = z > max ? z : max;
    }

    return std::make_pair(min, max);
}

std::pair<float, float> findMinMaxElements(const glkernel::tkernel<glm::vec4> & kernel)
{
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::min();

    for (const auto & element : kernel)
    {
        const auto x = element.x;
        const auto y = element.y;
        const auto z = element.z;
        const auto w = element.w;

        min = x < min ? x : min;
        min = y < min ? y : min;
        min = z < min ? z : min;
        min = w < min ? w : min;

        max = x > max ? x : max;
        max = y > max ? y : max;
        max = z > max ? z : max;
        max = w > max ? w : max;
    }

    return std::make_pair(min, max);
}

bool canBeFloat(const cppexpose::Variant & v)
{
    return v.canConvert<float>();
}

bool canBeVec2(const cppexpose::Variant & v)
{
    const auto arr = v.asArray();

    if (!arr)
        return false;

    if (arr->size() < 2)
        return false;

    return canBeFloat(arr->at(0)) && canBeFloat(arr->at(1));
}

bool canBeVec3(const cppexpose::Variant & v)
{
    const auto arr = v.asArray();

    if (!arr)
        return false;

    if (arr->size() < 3)
        return false;

    return canBeFloat(arr->at(0)) && canBeFloat(arr->at(1)) && canBeFloat(arr->at(2));
}

bool canBeVec4(const cppexpose::Variant & v)
{
    const auto arr = v.asArray();

    if (!arr)
        return false;

    if (arr->size() < 4)
        return false;

    return canBeFloat(arr->at(0)) && canBeFloat(arr->at(1)) && canBeFloat(arr->at(2)) && canBeFloat(arr->at(3));
}

float variantToFloat(const cppexpose::Variant & v)
{
    return v.value<float>();
}

glm::vec2 variantToVec2(const cppexpose::Variant & v)
{
    const auto arr = v.asArray();

    const auto x = variantToFloat(arr->at(0));
    const auto y = variantToFloat(arr->at(1));

    return glm::vec2(x,y);
}

glm::vec3 variantToVec3(const cppexpose::Variant & v)
{
    const auto arr = v.asArray();

    const auto x = variantToFloat(arr->at(0));
    const auto y = variantToFloat(arr->at(1));
    const auto z = variantToFloat(arr->at(2));

    return glm::vec3(x,y,z);
}

glm::vec4 variantToVec4(const cppexpose::Variant & v)
{
    const auto arr = v.asArray();

    const auto x = variantToFloat(arr->at(0));
    const auto y = variantToFloat(arr->at(1));
    const auto z = variantToFloat(arr->at(2));
    const auto w = variantToFloat(arr->at(3));

    return glm::vec4(x,y,z,w);
}
