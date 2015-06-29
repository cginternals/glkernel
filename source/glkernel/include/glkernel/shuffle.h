#pragma once

#include <glm/gtc/type_precision.hpp>

#include <glkernel/kernel.h>


namespace glkernel
{

class shuffle
{
    shuffle() = delete;

public:

    template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
    static void bucket_permutate(tkernel<T> & kernel, glm::uint16 width, glm::uint16 height, glm::uint16 depth);
};

} // namespace glkernel

#include <glkernel/sequence.hpp>
