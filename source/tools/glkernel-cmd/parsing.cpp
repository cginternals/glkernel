#include "parsing.h"

#include <iostream>

#include <glkernel/Kernel.h>
#include <glkernel/noise.h>

#include <cppexpose/json/JSON.h>

namespace
{
    template <typename T>
    void processCommand(glkernel::tkernel<T>& kernel, const std::string& command, const cppexpose::VariantMap& arguments)
    {
        if (command == "noise.uniform")
        {
            glkernel::noise::uniform(kernel, 0.0f, 1.0f);
        }
        else
        {
            std::cout << "Command " << command << " is unknown. It is skipped." << std::endl;
        }
    }

    template <typename T>
    void processCommands(glkernel::tkernel<T>& kernel, const cppexpose::VariantArray& commandArray)
    {
        for (auto& command : commandArray)
        {
            auto commandMap = command.asMap();

            auto& element = *commandMap->begin();

            auto& commandName = element.first;
            auto& arguments = element.second;

            auto argumentMap = arguments.asMap();

            processCommand(kernel, commandName, *argumentMap);
        }
    }
}

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

    if (rootMap->find("commands") == rootMap->end())
    {
        return false;
    }

    auto commandJson = rootMap->at("commands");
    auto commandArray = commandJson.asArray();

    if (components == 4)
    {
        glkernel::kernel4 kernel{ width, height, depth };

        processCommands(kernel, *commandArray);

        kernelVariant = cppexpose::Variant::fromValue(kernel);

        return true;
    }
    else if (components == 3)
    {
        glkernel::kernel3 kernel{ width, height, depth };

        processCommands(kernel, *commandArray);

        kernelVariant = cppexpose::Variant::fromValue(kernel);

        return true;
    }
    else if (components == 2)
    {
        glkernel::kernel2 kernel{ width, height, depth };

        processCommands(kernel, *commandArray);

        kernelVariant = cppexpose::Variant::fromValue(kernel);

        return true;
    }
    else if (components == 1)
    {
        glkernel::kernel1 kernel{ width, height, depth };

        processCommands(kernel, *commandArray);

        kernelVariant = cppexpose::Variant::fromValue(kernel);

        return true;
    }

    return false;
}
