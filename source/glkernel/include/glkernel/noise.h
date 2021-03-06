
#pragma once

#include <type_traits>

#include <random>

#include <glm/gtc/type_precision.hpp>

#include <glkernel/Kernel.h>


namespace glkernel
{


namespace noise
{


template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
void uniform(tkernel<T> & kernel, T range_min, T range_max);

template <typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type * = nullptr>
void uniform(tkernel<V> & kernel, typename V::value_type range_min, typename V::value_type range_max);

template <typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type * = nullptr>
void uniform(tkernel<V> & kernel, const V & range_min, const V & range_max);


template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
void normal(tkernel<T> & kernel, T mean, T stddev);

template <typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type * = nullptr>
void normal(tkernel<V> & kernel, typename V::value_type mean, typename V::value_type stddev);

template <typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type * = nullptr>
void normal(tkernel<V> & kernel, const V & mean, const V & stddev);

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
