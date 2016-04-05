#pragma once

#include <glm/gtc/type_precision.hpp>

#include <glkernel/Kernel.h>


namespace glkernel
{

namespace sort
{

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void distance(tkernel<V<T, P>> & kernel, const V<T, P> & origin);

} // namespace sort

} // namespace glkernel

#include <glkernel/sort.hpp>
