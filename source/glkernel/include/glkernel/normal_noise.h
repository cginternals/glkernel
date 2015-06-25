#pragma once

#include <glkernel/glkernel_api.h>

#include <glm/vec2.hpp>

#include <glkernel/Kernel.h>


namespace glkernel
{

// generates gaussian distributed random values for given mean and standard deviation

//template<typename T>
//void normal_noise(Kernel<T> & kernel, const T mean, const T stddev);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void normal_noise(Kernel<V<T, P>> & kernel, const T mean, const T stddev);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void normal_noise(Kernel<V<T, P>> & kernel, const V<T, P> & mean, const V<T, P> & stddev);

} // namespace glkernel

#include <glkernel/normal_noise.hpp>
