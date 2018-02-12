
#pragma once

#include <glm/gtc/type_precision.hpp>

#include <glkernel/Kernel.h>


namespace glkernel
{


namespace scale
{

template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
void range(tkernel<T> & kernel, T rangeToLower, T rangeToUpper, T rangeFromLower = 0, T rangeFromUpper = 1);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void range(tkernel<V<T, P>> & kernel, T rangeToLower, T rangeToUpper, T rangeFromLower = 0, T rangeFromUpper = 1);


} // namespace scale


} // namespace glkernel


#include <glkernel/scale.hpp>
