#pragma once

#include <glkernel/noise.h>

#include <glkernel/glm_compatability.h>


namespace glkernel
{

namespace noise
{


template<typename T>
uniform_operator<T>::uniform_operator(const size_t, const glm::length_t
    , const T range_min, const T range_max)
: m_generator{ std::random_device{ }() }
, m_distribute{ range_min, range_max }
{
}

template <typename T>
template <typename F, glm::precision P, template<typename, glm::precision> class V>
uniform_operator<T>::uniform_operator(const size_t size, const glm::length_t coefficient
    , const V<F, P> & range_min, const V<F, P> range_max)
: uniform_operator{ size, coefficient, range_min[coefficient], range_max[coefficient] }
{
}

template<typename T>
T uniform_operator<T>::operator()(const size_t)
{
    return m_distribute(m_generator);
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
void uniform(tkernel<T> & kernel, const T range_min, const T range_max)
{
    kernel.for_each<uniform_operator<T>>(range_min, range_max);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<V<T, P>> & kernel, const T range_min, const T range_max)
{
    kernel.for_each<uniform_operator<T>>(range_min, range_max);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<V<T, P>> & kernel, const V<T, P> & range_min, const V<T, P> & range_max)
{
    kernel.for_each<uniform_operator<T>>(range_min, range_max);
}


template <typename T>
normal_operator<T>::normal_operator(const size_t, const glm::length_t
    , const T mean, const T stddev)
: m_generator{ std::random_device{}() }
, m_distribute{ mean, stddev }
{
}

template <typename T>
template <typename F, glm::precision P, template<typename, glm::precision> class V>
normal_operator<T>::normal_operator(const size_t size, const glm::length_t coefficient
    , const V<F, P> & mean, const V<F, P> stddev)
: normal_operator{ size, coefficient, mean[coefficient], stddev[coefficient] }
{
}

template<typename T>
T normal_operator<T>::operator()(const size_t)
{
    return m_distribute(m_generator);
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
void normal(tkernel<T> & kernel, const T mean, const T stddev)
{
    kernel.for_each<normal_operator<T>>(mean, stddev);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void normal(tkernel<V<T, P>> & kernel, const T mean, const T stddev)
{
    kernel.for_each<normal_operator<T>>(mean, stddev);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void normal(tkernel<V<T, P>> & kernel, const V<T, P> & mean, const V<T, P> & stddev)
{
    kernel.for_each<normal_operator<T>>(mean, stddev);
}


} // namespace noise

} // namespace glkernel
