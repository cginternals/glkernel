#include "KernelJsonImporter.h"

#include <glkernel/Kernel.h>

#include <cppassist/logging/logging.h>

void assert_msg(bool condition, const std::string& msg)
{
    if (!condition)
    {
        throw std::logic_error(msg);
    }
}

void forEachCell(cppexpose::VariantArray * depthArray, std::function<void(const cppexpose::Variant&)> lambda)
{
    assert_msg(depthArray, "Malformed kernel input.");

    for (const auto& heightVariant : *depthArray)
    {
        auto heightArray = heightVariant.asArray();
        assert_msg(heightArray, "Malformed kernel input.");

        for (const auto& widthVariant : *heightArray)
        {
            auto widthArray = widthVariant.asArray();
            assert_msg(widthArray, "Malformed kernel input.");

            for (const auto& elementVariant : *widthArray)
            {
                lambda(elementVariant);
            }
        }
    }
}

// TODO: this is duplicated in the generated code, remove this duplication
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

KernelJsonImporter::KernelJsonImporter(const std::string& inputFileName)
{
    cppexpose::Variant root;

    bool success = cppexpose::JSON::load(root, inputFileName);
    assert_msg(success, "JSON could not be loaded.");

    auto rootMap = root.asMap();
    assert_msg(rootMap, "Input JSON is malformed.");

    auto depthArray = rootMap->at("kernel").asArray();
    auto sizeMap = rootMap->at("size").asMap();

    int depth = sizeMap->at("depth").value<int>();
    int height = sizeMap->at("height").value<int>();
    int width = sizeMap->at("width").value<int>();
    int numComponents = -1;

    // assert that all cells have the same cell type
    forEachCell(depthArray, [&numComponents](const cppexpose::Variant& elementVariant) {
        if (elementVariant.isFloatingPoint())
        {
            assert_msg(numComponents == -1 || numComponents == 1,
                       "All cells must have the same cell type (float, vec2, vec3 or vec4).");

            numComponents = 1;
        }
        else
        {
            assert_msg(elementVariant.isArray(), "Cell is not floating point or array.");

            assert_msg(numComponents == -1 || elementVariant.asArray()->size() == numComponents,
                    "All cells must have the same cell type (float, vec2, vec3 or vec4).");

            numComponents = elementVariant.asArray()->size();
        }
    });

    int i = 0;

    if (numComponents == 1)
    {
        glkernel::kernel1 kernel(width, height, depth);

        forEachCell(depthArray, [&i, &kernel](const cppexpose::Variant& elementVariant) {
            kernel[i] = variantToFloat(elementVariant);
            i++;
        });

        m_kernelVariant = cppexpose::Variant::fromValue(kernel);
    }
    else if (numComponents == 2)
    {
        glkernel::kernel2 kernel(width, height, depth);

        forEachCell(depthArray, [&i, &kernel](const cppexpose::Variant& elementVariant) {
            kernel[i] = variantToVec2(elementVariant);
            i++;
        });

        m_kernelVariant = cppexpose::Variant::fromValue(kernel);
    }
    else if (numComponents == 3)
    {
        glkernel::kernel3 kernel(width, height, depth);

        forEachCell(depthArray, [&i, &kernel](const cppexpose::Variant& elementVariant) {
            kernel[i] = variantToVec3(elementVariant);
            i++;
        });

        m_kernelVariant = cppexpose::Variant::fromValue(kernel);
    }
    else if (numComponents == 4)
    {
        glkernel::kernel4 kernel(width, height, depth);

        forEachCell(depthArray, [&i, &kernel](const cppexpose::Variant& elementVariant) {
            kernel[i] = variantToVec4(elementVariant);
            i++;
        });

        m_kernelVariant = cppexpose::Variant::fromValue(kernel);
    }
    else
    {
        cppassist::error() << "Invalid number of components.";
    }
}

cppexpose::Variant KernelJsonImporter::getKernel()
{
    return m_kernelVariant;
}
