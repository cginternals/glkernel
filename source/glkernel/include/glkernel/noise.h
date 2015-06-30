#pragma once

#include <type_traits>

#include <random>

#include <glm/gtc/type_precision.hpp>

#include <glkernel/kernel.h>


namespace glkernel
{

namespace noise
{


template <typename T>
class uniform_operator
{
public:
    uniform_operator(size_t size, glm::length_t
        , T range_min, T range_max);

    template <typename F, glm::precision P, template<typename, glm::precision> class V>
    uniform_operator(size_t size, glm::length_t coefficient
        , const V<F, P> & range_min, const V<F, P> range_max);

    T operator()(const size_t index);

protected:
    std::mt19937_64 m_generator;
    std::uniform_real_distribution<T> m_distribute;
};

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
void uniform(tkernel<T> & kernel, T range_min, T range_max);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<V<T, P>> & kernel, T range_min, T range_max);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<V<T, P>> & kernel, const V<T, P> & range_min, const V<T, P> & range_max);


template <typename T>
class normal_operator
{
public:
    normal_operator(size_t size, glm::length_t
        , T mean, T stddev);

    template <typename F, glm::precision P, template<typename, glm::precision> class V>
    normal_operator(size_t size, glm::length_t coefficient
        , const V<F, P> & mean, const V<F, P> stddev);

    T operator()(const size_t index);

protected:
    std::mt19937_64 m_generator;
    std::uniform_real_distribution<T> m_distribute;
};

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
void normal(tkernel<T> & kernel, T mean, T stddev);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void normal(tkernel<V<T, P>> & kernel, T mean, T stddev);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void normal(tkernel<V<T, P>> & kernel, const V<T, P> & mean, const V<T, P> & stddev);


} // namespace noise

} // namespace glkernel

#include <glkernel/noise.hpp>
