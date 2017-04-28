#include "variantConversion.h"

cppexpose::Variant toVariant(const glkernel::kernel3& kernel)
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

                const auto& value = kernel.value(x, y, z);

                elementArray.asArray()->push_back(value.x);
                elementArray.asArray()->push_back(value.y);
                elementArray.asArray()->push_back(value.z);

                xArray.asArray()->push_back(elementArray);
            }

            yArray.asArray()->push_back(xArray);
        }

        zArray.asArray()->push_back(yArray);
    }

    cppexpose::Variant result = cppexpose::Variant::map();

    result.asMap()->emplace("height", kernel.height());
    result.asMap()->emplace("width", kernel.width());
    result.asMap()->emplace("depth", kernel.depth());
    result.asMap()->emplace("kernel", zArray);

    return result;
}
