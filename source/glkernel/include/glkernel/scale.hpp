
#pragma once

#include <glkernel/scale.h>

#include <glkernel/glm_compatability.h>


namespace glkernel
{


namespace scale
{


template <typename T>
class range_operator
{
public:
    range_operator(const glm::u16vec3 & extent, glm::length_t, T rangeToLower, T rangeToUpper, T rangeFromLower, T rangeFromUpper);

    template <typename F, glm::precision P, template<typename, glm::precision> class V>
    range_operator(const glm::u16vec3 & extent, glm::length_t coefficient, T rangeToLower, T rangeToUpper, T rangeFromLower, T rangeFromUpper);

    T operator()(const T element);

protected:
    const T m_factor;
    const T m_summand;
};


template<typename T>
range_operator<T>::range_operator(
    const glm::u16vec3 & /*extent*/, const glm::length_t /*coefficient*/,
    T rangeToLower, T rangeToUpper, T rangeFromLower, T rangeFromUpper)
: m_factor{ (rangeToUpper - rangeToLower) / (rangeFromUpper - rangeFromLower) }
, m_summand{ rangeToLower - rangeFromLower * m_factor }
{
}

template <typename T>
template <typename F, glm::precision P, template<typename, glm::precision> class V>
range_operator<T>::range_operator(
    const glm::u16vec3 & extent, const glm::length_t coefficient,
    T rangeToLower, T rangeToUpper, T rangeFromLower, T rangeFromUpper)
: range_operator{ extent, coefficient, rangeToLower, rangeToUpper, rangeFromLower, rangeFromUpper}
{
}

template<typename T>
T range_operator<T>::operator()(const T element)
{
    return element * m_factor + m_summand;
}

template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
void range(tkernel<T> & kernel, T rangeToLower, T rangeToUpper, T rangeFromLower, T rangeFromUpper)
{
    kernel.template for_each_element<range_operator<T>>(rangeToLower, rangeToUpper, rangeFromLower, rangeFromUpper);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void range(tkernel<V<T, P>> & kernel, T rangeToLower, T rangeToUpper, T rangeFromLower, T rangeFromUpper)
{
    kernel.template for_each_element<range_operator<T>>(rangeToLower, rangeToUpper, rangeFromLower, rangeFromUpper);
}


} // namespace scale


} // namespace glkernel
