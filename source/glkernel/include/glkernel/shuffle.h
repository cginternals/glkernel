#pragma once

#include <glm/gtc/type_precision.hpp>

#include <glkernel/Kernel.h>


namespace glkernel
{

namespace shuffle
{

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
void bucket_permutate(tkernel<T> & kernel
    , glm::uint16 subkernel_width  = 1
    , glm::uint16 subkernel_height = 1
    , glm::uint16 subkernel_depth  = 1
    , const bool permutate_per_bucket = false);

// uses classic bayer matrices for kernel sizes 4, 9, 16, and 64 to remap the kernel
// Note: kernel remains unchanged if its size is unsupported 
template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
void bayer(tkernel<T> & kernel);

// uses std::random_shuffle
template<typename T>
void random(tkernel<T> & kernel, size_t start = 1);

} // namespace shuffle

} // namespace glkernel

#include <glkernel/shuffle.hpp>
