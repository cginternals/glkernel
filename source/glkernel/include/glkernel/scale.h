
#pragma once

#include <glm/gtc/type_precision.hpp>

#include <glkernel/Kernel.h>


namespace glkernel
{


namespace scale
{

template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
void range(tkernel<T> & kernel, T rangeToLower, T rangeToUpper, T rangeFromLower = 0, T rangeFromUpper = 1);

template <typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type * = nullptr>
void range(tkernel<V> & kernel, typename V::value_type rangeToLower, typename V::value_type rangeToUpper, typename V::value_type rangeFromLower = 0, typename V::value_type rangeFromUpper = 1);


} // namespace scale


} // namespace glkernel


#include <glkernel/scale.hpp>
