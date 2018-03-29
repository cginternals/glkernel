
#pragma once

#include <glm/gtc/type_precision.hpp>

#include <glkernel/Kernel.h>


namespace glkernel
{


namespace sort
{


template <typename T>
void distance(tkernel<T> & kernel, const T & origin);


} // namespace sort


} // namespace glkernel


#include <glkernel/sort.hpp>

#include <glkernel-generalizations/sort_generalized.h>
