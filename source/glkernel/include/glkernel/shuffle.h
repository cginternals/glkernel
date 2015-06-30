#pragma once

#include <glm/gtc/type_precision.hpp>

#include <glkernel/kernel.h>


namespace glkernel
{

namespace shuffle
{

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
void bucket_permutate(tkernel<T> & kernel, glm::uint16 subkernel_width = 1, glm::uint16 subkernel_height = 1, glm::uint16 subkernel_depth = 1);

} // namespace shuffle

} // namespace glkernel

#include <glkernel/shuffle.hpp>
