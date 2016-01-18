#pragma once

#include <type_traits>

#include <random>

#include <glm/gtc/type_precision.hpp>

#include <glkernel/Kernel.h>


namespace glkernel
{

namespace noise
{


template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
void uniform(tkernel<T> & kernel, T range_min, T range_max);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<V<T, P>> & kernel, T range_min, T range_max);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<V<T, P>> & kernel, const V<T, P> & range_min, const V<T, P> & range_max);


template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
void normal(tkernel<T> & kernel, T mean, T stddev);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void normal(tkernel<V<T, P>> & kernel, T mean, T stddev);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void normal(tkernel<V<T, P>> & kernel, const V<T, P> & mean, const V<T, P> & stddev);

/**
*  @brief
*  Type of gradient noise
*/
enum class GradientNoiseType : unsigned char
{
    Perlin,
    Simplex
};

/**
*  @brief
*  Type used for octaving gradient noise
*/
enum class OctaveType : unsigned char
{
	Standard,
	Cloud,
	CloudAbs,
	Wood,
	Paper
};

/**
*  @brief
*  Computes a gradient noise dependingon the GradientNoiseType chosen
*  Currently supported:
*  - Improved tilable 3D perlin noise
*  - non-tilable simplex noise
*
*  Uses the random numbers generated by Ken Perlin for the computation
*
*  @param[in,out] kernel
*  The kernel to be modified, size is used for number of samples
*
*  @param[in] noise_type
*  The type of noise to be generated
*
*  @param[in] octave_type
*  Method of combining different octaves
*
*  @param[in] startFrequency
*  Lowest frequency noise is generated at
*
*  @param[in,out] octaves
*  Number of frequencies used for noise generation
*/
template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
void gradient(tkernel<T> & kernel
    , const GradientNoiseType noise_type = GradientNoiseType::Perlin
    , const OctaveType octave_type = OctaveType::Standard
    , const unsigned int startFrequency = 3
    , const unsigned int octaves = 5);


} // namespace noise

} // namespace glkernel

#include <glkernel/noise.hpp>
