#include "parsing.h"

#include <glkernel/Kernel.h>
#include <cppexpose/json/JSON.h>

bool generateKernelFromJSON(cppexpose::Variant& kernelVariant, const std::string& filePath)
{
    cppexpose::Variant root;

    if (!cppexpose::JSON::load(root, filePath))
    {
        return false;
    }

    if (!root.isVariantMap())
    {
        return false;
    }

    auto rootMap = root.asMap();

    if (rootMap->find("init-kernel") == rootMap->end())
    {
        return false;
    }

    auto initKernel = rootMap->at("init-kernel");
    auto initKernelMap = initKernel.asMap();

    auto components = initKernelMap->at("components").value<int>();

    auto width = initKernelMap->at("width").value<glm::uint16>();
    auto height = initKernelMap->at("height").value<glm::uint16>();
    auto depth = initKernelMap->at("depth").value<glm::uint16>();

    if (components == 4)
    {
        glkernel::kernel4 kernel{ width, height, depth };

        kernelVariant = cppexpose::Variant::fromValue(kernel);

        return true;
    }
    if (components == 3)
    {
        glkernel::kernel3 kernel{ width, height, depth };

        kernelVariant = cppexpose::Variant::fromValue(kernel);

        return true;
    }
    else if (components == 2)
    {
        glkernel::kernel2 kernel{ width, height, depth };

        kernelVariant = cppexpose::Variant::fromValue(kernel);

        return true;
    }
    else if (components == 1)
    {
        glkernel::kernel1 kernel{ width, height, depth };

        kernelVariant = cppexpose::Variant::fromValue(kernel);

        return true;
    }

    return false;
}
