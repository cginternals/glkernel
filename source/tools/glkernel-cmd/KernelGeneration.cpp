#include "KernelGeneration.h"

#include <iostream>

#include <glkernel/Kernel.h>
#include <glkernel/noise.h>
#include <glkernel/sample.h>
#include <glkernel/scale.h>
#include <glkernel/sequence.h>
#include <glkernel/shuffle.h>
#include <glkernel/sort.h>

#include <cppexpose/json/JSON.h>

namespace
{
    template <typename T>
    void processPoissonSquare(glkernel::tkernel<T> & kernel, unsigned int num_probes)
    {
        std::cout << "Poisson square is not implemented for the specified kernel type. Only kernel2 is supported." << std::endl;
    }

    template <>
    void processPoissonSquare<glm::vec2>(glkernel::kernel2 & kernel, unsigned int num_probes)
    {
        glkernel::sample::poisson_square(kernel, num_probes);
    }

    template <typename T>
    void processStratified(glkernel::tkernel<T> & kernel)
    {
    }

    template <>
    void processStratified<float>(glkernel::kernel1 & kernel)
    {
        glkernel::sample::stratified(kernel);
    }

    template <>
    void processStratified<glm::vec2>(glkernel::kernel2 & kernel)
    {
        glkernel::sample::stratified(kernel);
    }

    template <>
    void processStratified<glm::vec3>(glkernel::kernel3 & kernel)
    {
        glkernel::sample::stratified(kernel);
    }

    template <>
    void processStratified<glm::vec4>(glkernel::kernel4 & kernel)
    {
        std::cout << "Stratified is not implemented for kernel4." << std::endl;
    }

    template <typename T>
    void processHammersley(glkernel::tkernel<T> & kernel)
    {
        std::cout << "Hammersley is not implemented for the specified kernel type. Only kernel2 is supported." << std::endl;
    }

    template <>
    void processHammersley<glm::vec2>(glkernel::kernel2& kernel)
    {
        glkernel::sample::hammersley(kernel);
    }

    template <typename T>
    void processHalton(glkernel::tkernel<T> & kernel, uint base1, uint base2)
    {
        std::cout << "Hammersley is not implemented for the specified kernel type. Only kernel2 is supported." << std::endl;
    }

    template <>
    void processHalton<glm::vec2>(glkernel::kernel2 & kernel, uint base1, uint base2)
    {
        glkernel::sample::halton(kernel, base1, base2);
    }

    template <typename T>
    void processHammersleySphere(glkernel::tkernel<T> & kernel)
    {
        std::cout << "Hammersley is not implemented for the specified kernel type. Only kernel3 is supported." << std::endl;
    }

    template <>
    void processHammersleySphere<glm::vec3>(glkernel::kernel3 & kernel)
    {
        glkernel::sample::hammersley_sphere(kernel);
    }

    template <typename T>
    void processHaltonSphere(glkernel::tkernel<T> & kernel, uint base1, uint base2)
    {
        std::cout << "Hammersley is not implemented for the specified kernel type. Only kernel3 is supported." << std::endl;
    }

    template <>
    void processHaltonSphere<glm::vec3>(glkernel::kernel3 & kernel, uint base1, uint base2)
    {
        glkernel::sample::halton_sphere(kernel, base1, base2);
    }

    template <typename T>
    void processBestCandidate(glkernel::tkernel<T> & kernel, uint numCandidates)
    {
        std::cout << "Best Candidate is not implemented for the specified kernel type. Only kernel2 and kernel3 are supported." << std::endl;
    }

    template <>
    void processBestCandidate<glm::vec2>(glkernel::kernel2 & kernel, uint numCandidates)
    {
        glkernel::sample::best_candidate(kernel, numCandidates);
    }

    template <>
    void processBestCandidate<glm::vec3>(glkernel::kernel3 & kernel, uint numCandidates)
    {
        glkernel::sample::best_candidate(kernel, numCandidates);
    }

    template <typename T>
    void processNRooks(glkernel::tkernel<T> & kernel)
    {
        std::cout << "N rooks is not implemented for the specified kernel type. Only kernel2 is supported." << std::endl;
    }

    template <>
    void processNRooks<glm::vec2>(glkernel::kernel2 & kernel)
    {
        glkernel::sample::n_rooks(kernel);
    }

    template <typename T>
    void processMultiJittered(glkernel::tkernel<T> & kernel)
    {
        std::cout << "Multi jittered is not implemented for the specified kernel type. Only kernel2 is supported." << std::endl;
    }

    template <>
    void processMultiJittered<glm::vec2>(glkernel::kernel2 & kernel)
    {
        glkernel::sample::multi_jittered(kernel);
    }

    template <typename T>
    void processGoldenPointSet(glkernel::tkernel<T> & kernel)
    {
        std::cout << "Golden point set is not implemented for the specified kernel type. Only kernel2 is supported." << std::endl;
    }

    template <>
    void processGoldenPointSet<glm::vec2>(glkernel::kernel2 & kernel)
    {
        glkernel::sample::golden_point_set(kernel);
    }

    template <typename T>
    void processCommand(glkernel::tkernel<T> & kernel, const std::string & command, const cppexpose::VariantMap & arguments)
    {
        auto parseArg = [&](const std::string& argName, const float stdValue) -> float
        {
            if (arguments.find(argName) == arguments.end())
            {
                std::cout << "Argument " << argName << " was not supplied to command " << command << ". Assuming standard value of " << stdValue << "." << std::endl;
                return stdValue;
            }

            return arguments.at(argName).value<float>();
        };

        // Noise
        if (command == "noise.uniform")
        {
            glkernel::noise::uniform(kernel, parseArg("range_min", 0.0f), parseArg("range_max", 1.0f));
        }
        else if (command == "noise.normal")
        {
            glkernel::noise::normal(kernel, parseArg("mean", 0.0f), parseArg("stddev", 1.0f));
        }

        // Sampling
        else if (command == "sample.poisson_square")
        {
            processPoissonSquare(kernel, parseArg("num_probes", 32));
        }
        else if (command == "sample.stratified")
        {
            processStratified(kernel);
        }
        else if (command == "sample.hammersley")
        {
            processHammersley(kernel);
        }
        else if (command == "sample.hammersley_sphere")
        {
            processHammersleySphere(kernel);
        }
        else if (command == "sample.halton")
        {
            processHalton(kernel, parseArg("base1", 2), parseArg("base2", 2));
        }
        else if (command == "sample.halton_sphere")
        {
            processHaltonSphere(kernel, parseArg("base1", 2), parseArg("base2", 2));
        }
        else if (command == "sample.best_candidate")
        {
            processBestCandidate(kernel, parseArg("num_candidates", 32));
        }
        else if (command == "sample.n_rooks")
        {
            processNRooks(kernel);
        }
        else if (command == "sample.multi_jittered")
        {
            processMultiJittered(kernel);
        }
        else if (command == "sample.golden_point_set")
        {
            processGoldenPointSet(kernel);
        }

        // Scale
        else if (command == "scale.range")
        {
            glkernel::scale::range(kernel, parseArg("range_to_lower", 0.0f), parseArg("range_to_upper", 1.0f), parseArg("range_from_lower", 0.0f), parseArg("range_from_upper", 1.0f));
        }

        // Sequence
        else if (command == "sequence.uniform")
        {
            glkernel::sequence::uniform(kernel, parseArg("range_min", 0.0f), parseArg("range_max", 1.0f));
        }

        // Shuffle
        else if (command == "shuffle.bucket_permutate")
        {
            glkernel::shuffle::bucket_permutate(kernel, parseArg("subkernel_width", 1), parseArg("subkernel_height", 1), parseArg("subkernel_depth", 1));
        }
        else if (command == "shuffle.bayer")
        {
            glkernel::shuffle::bayer(kernel);
        }
        else if (command == "shuffle.random")
        {
            glkernel::shuffle::random(kernel, parseArg("start", 1));
        }

        // Sort
        else if (command == "sort.distance")
        {
            // TODO: read origin, needs to be based on T
            glkernel::sort::distance(kernel, T());
        }
        else
        {
            std::cout << "Command " << command << " is unknown. It is skipped." << std::endl;
        }
    }

    template <typename T>
    void processCommands(glkernel::tkernel<T> & kernel, const cppexpose::VariantArray & commandArray)
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

bool generateKernelFromDescription(cppexpose::Variant & kernelVariant, const std::string & filePath)
{
    cppexpose::Variant root;

    if (!cppexpose::JSON::load(root, filePath))
    {
        std::cerr << "Input file could not be loaded." << std::endl;
        return false;
    }

    if (!root.isVariantMap())
    {
        std::cerr << "Invalid JSON format. JSON does not contain a JSON object" << std::endl;
        return false;
    }

    auto rootMap = root.asMap();

    if (rootMap->find("init-kernel") == rootMap->end())
    {
        std::cerr << "Invalid JSON format. Entry 'init-kernel' not found. " << std::endl;
        return false;
    }

    auto initKernel = rootMap->at("init-kernel");
    auto initKernelMap = initKernel.asMap();

    if (!initKernelMap)
    {
        std::cerr << "Invalid JSON format. Entry 'init-kernel' does not contain a JSON object. " << std::endl;
        return false;
    }

    auto components = initKernelMap->at("components").value<int>();

    auto width = initKernelMap->at("width").value<glm::uint16>();
    auto height = initKernelMap->at("height").value<glm::uint16>();
    auto depth = initKernelMap->at("depth").value<glm::uint16>();

    if (rootMap->find("commands") == rootMap->end())
    {
        std::cerr << "Invalid JSON format. Entry 'commands' not found. " << std::endl;
        return false;
    }

    auto commandJson = rootMap->at("commands");
    auto commandArray = commandJson.asArray();

    if (!commandArray)
    {
        std::cerr << "Invalid JSON format. Entry 'commands' is not a JSON array. " << std::endl;
        return false;
    }

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
