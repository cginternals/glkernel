#pragma once

#include <glkernel/sequence.h>

#include <glkernel/glm_compatability.h>


namespace glkernel
{

namespace sequence
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
    T m_range_min;
    T m_range_max;

    size_t m_size;
};


template <typename T>
uniform_operator<T>::uniform_operator(const size_t size, const glm::length_t
    , const T range_min, const T range_max)
: m_range_min{ range_min }
, m_range_max{ range_max }
, m_size{ size }
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
T uniform_operator<T>::operator()(const size_t index)
{
    return m_range_min + (m_range_max - m_range_min) * index / (m_size - 1);
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
void uniform(tkernel<T> & kernel, const T range_min, const T range_max)
{
    kernel.template for_each<uniform_operator<T>>(range_min, range_max);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<V<T, P>> & kernel, const T range_min, const T range_max)
{
    kernel.template for_each<uniform_operator<T>>(range_min, range_max);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<V<T, P>> & kernel, const V<T, P> & range_min, const V<T, P> & range_max)
{
    kernel.template for_each<uniform_operator<T>>(range_min, range_max);
}


} // namesapce sequence

} // namespace glkernel
