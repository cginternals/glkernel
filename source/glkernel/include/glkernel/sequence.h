
#pragma once

#include <glm/gtc/type_precision.hpp>

#include <glkernel/Kernel.h>


namespace glkernel
{


namespace sequence
{


template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
void uniform(tkernel<T> & kernel, T range_min, T range_max);

template<typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type * = nullptr>
void uniform(tkernel<V> & kernel, typename V::value_type range_min, typename V::value_type range_max);

template<typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type * = nullptr>
void uniform(tkernel<V> & kernel, const V & range_min, const V & range_max);


} // namespace sequence


} // namespace glkernel


#include <glkernel/sequence.hpp>
