#pragma once

#include <glkernel/glkernel_api.h>

#include <glm/vec2.hpp>

#include <glkernel/Kernel.h>


namespace glkernel
{

template<typename T>
void white_noise(Kernel<T> & kernel, const T range_min, const T range_max);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void white_noise(Kernel<V<T, P>> & kernel, const T range_min, const T range_max);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void white_noise(Kernel<V<T, P>> & kernel, const V<T, P> & range_min, const V<T, P> & range_max);

} // namespace glkernel

#include <glkernel/white_noise.hpp>
