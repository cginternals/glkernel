#include "KernelJsonExporter.hpp"

#include <cppassist/logging/logging.h>

#include <iostream>
#include <fstream>
#include <algorithm>

void KernelJsonExporter::exportKernel() {
    const auto jsonArray = toJsonArray(m_kernel);

    writeToFile(jsonArray);
}

cppexpose::Variant KernelJsonExporter::toJsonArray(const cppexpose::Variant & kernelVariant) {

    auto kernelArray = cppexpose::Variant::array();

    if (kernelVariant.hasType<glkernel::kernel4>())
    {
        auto kernel = kernelVariant.value<glkernel::kernel4>();
        std::for_each(kernel.cbegin(), kernel.cend(), [&kernelArray, this](const glm::vec4 & component) {
            this->appendFloatValues(kernelArray.asArray(), { component.x, component.y, component.z, component.w });
        });
    }
    else if (kernelVariant.hasType<glkernel::kernel3>())
    {
        auto kernel = kernelVariant.value<glkernel::kernel3>();
        std::for_each(kernel.cbegin(), kernel.cend(), [&kernelArray, this](const glm::vec3 & component) {
            this->appendFloatValues(kernelArray.asArray(), { component.x, component.y, component.z });
        });
    }
    else if (kernelVariant.hasType<glkernel::kernel2>())
    {
        auto kernel = kernelVariant.value<glkernel::kernel2>();
        std::for_each(kernel.cbegin(), kernel.cend(), [&kernelArray, this](const glm::vec2 & component) {
            this->appendFloatValues(kernelArray.asArray(), { component.x, component.y });
        });
    }
    else if (kernelVariant.hasType<glkernel::kernel1>())
    {
        auto kernel = kernelVariant.value<glkernel::kernel1>();
        std::for_each(kernel.cbegin(), kernel.cend(), [&kernelArray, this](const float component) {
            this->appendFloatValues(kernelArray.asArray(), { component });
        });
    }
    else
    {
        cppassist::error() << "Unknown kernel type found. Aborting...";
        return cppexpose::Variant::fromValue(glkernel::kernel1{ });
    }

    cppexpose::Variant result = cppexpose::Variant::map();
    cppexpose::Variant size = cppexpose::Variant::map();

    size.asMap()->emplace("height", 1); // TODO actual values
    size.asMap()->emplace("width", 1);
    size.asMap()->emplace("depth", 1);

    result.asMap()->emplace("size", size);
    result.asMap()->emplace("kernel", kernelArray);

    return result;
}

void KernelJsonExporter::appendFloatValues(cppexpose::VariantArray * kernelArray, std::initializer_list<float> component) {
    auto componentArrayVariant = cppexpose::Variant::array();
    auto componentArray = componentArrayVariant.asArray();
    componentArray->insert(componentArray->end(), component.begin(), component.end());
    kernelArray->push_back(componentArrayVariant);

}


void KernelJsonExporter::writeToFile(const cppexpose::Variant & jsonArray) {
    std::ofstream outStream(m_outFileName);

    if (!outStream.is_open())
    {
        std::cerr << "ERROR: Output file could not be created. Aborting..." << std::endl;
        return;
    }

    outStream << stringify(jsonArray) << std::endl;
}

std::string KernelJsonExporter::stringify(const cppexpose::Variant &array) {
    return cppexpose::JSON::stringify(array, cppexpose::JSON::OutputMode::Beautify);
}
