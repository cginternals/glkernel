#include "JsonImporter.h"

#include "helper.h"

#include <glkernel/Kernel.h>

#include <cppassist/logging/logging.h>

void forEachCell(cppexpose::VariantArray * depthArray, std::function<void(const cppexpose::Variant&, int)> lambda)
{
    throwIfNot(depthArray, "Malformed kernel input.");

    int index = 0;

    for (const auto& heightVariant : *depthArray)
    {
        auto heightArray = heightVariant.asArray();
        throwIfNot(heightArray, "Malformed kernel input.");

        for (const auto& widthVariant : *heightArray)
        {
            auto widthArray = widthVariant.asArray();
            throwIfNot(widthArray, "Malformed kernel input.");

            for (const auto& elementVariant : *widthArray)
            {
                lambda(elementVariant, index);
                index++;
            }
        }
    }
}

JsonImporter::JsonImporter(const std::string& inputFileName)
{
    cppexpose::Variant root;

    bool success = cppexpose::JSON::load(root, inputFileName);
    throwIfNot(success, "JSON could not be loaded.");

    auto rootMap = root.asMap();
    throwIfNot(rootMap, "Input JSON is malformed.");

    auto depthArray = rootMap->at("kernel").asArray();
    auto sizeMap = rootMap->at("size").asMap();

    int depth = sizeMap->at("depth").value<int>();
    int height = sizeMap->at("height").value<int>();
    int width = sizeMap->at("width").value<int>();
    auto numComponents = 0u;

    // assert that all cells have the same cell type
    forEachCell(depthArray, [&numComponents](const cppexpose::Variant& elementVariant, int index) {
        if (elementVariant.isFloatingPoint())
        {
            throwIf(index > 0 && numComponents != 1u,
                       "All cells must have the same cell type (float, vec2, vec3 or vec4).");

            numComponents = 1;
        }
        else
        {
            throwIfNot(elementVariant.isVariantArray(), "Cell is not floating point or array.");
            throwIf(numComponents > 0 && numComponents != elementVariant.asArray()->size(),
                    "All cells must have the same cell type (float, vec2, vec3 or vec4).");

            numComponents = elementVariant.asArray()->size();
        }
    });

    if (numComponents == 1)
    {
        glkernel::kernel1 kernel(width, height, depth);

        forEachCell(depthArray, [&kernel](const cppexpose::Variant& elementVariant, int index) {
            kernel[index] = variantToFloat(elementVariant);
        });

        m_kernelVariant = cppexpose::Variant::fromValue(kernel);
    }
    else if (numComponents == 2)
    {
        glkernel::kernel2 kernel(width, height, depth);

        forEachCell(depthArray, [&kernel](const cppexpose::Variant& elementVariant, int index) {
            kernel[index] = variantToVec2(elementVariant);
        });

        m_kernelVariant = cppexpose::Variant::fromValue(kernel);
    }
    else if (numComponents == 3)
    {
        glkernel::kernel3 kernel(width, height, depth);

        forEachCell(depthArray, [&kernel](const cppexpose::Variant& elementVariant, int index) {
            kernel[index] = variantToVec3(elementVariant);
        });

        m_kernelVariant = cppexpose::Variant::fromValue(kernel);
    }
    else if (numComponents == 4)
    {
        glkernel::kernel4 kernel(width, height, depth);

        forEachCell(depthArray, [&kernel](const cppexpose::Variant& elementVariant, int index) {
            kernel[index] = variantToVec4(elementVariant);
        });

        m_kernelVariant = cppexpose::Variant::fromValue(kernel);
    }
    else
    {
        cppassist::error() << "Invalid number of components.";
    }
}

cppexpose::Variant JsonImporter::getKernel()
{
    return m_kernelVariant;
}
