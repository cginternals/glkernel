#pragma once

#include <glkernel/Kernel.h>

#include <cassert>
#include <type_traits>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace glkernel
{

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
T * kernel_ptr(std::vector<T> & kernel)
{
    return kernel.data();
}

template <typename T, typename std::enable_if<!std::is_floating_point<T>::value>::type *>
typename T::value_type * kernel_ptr(std::vector<T> & kernel)
{
    return glm::value_ptr(kernel.front());
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
glm::length_t kernel_length(const T &)
{
    return 1;
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
glm::length_t kernel_length(const V<T, P> & type)
{
    return type.length();
}


template<typename T>
tkernel<T>::tkernel(
    const glm::uint16 w
,   const glm::uint16 h
,   const glm::uint16 d)
: m_width { w }
, m_height{ h }
, m_depth { d }
{
    m_kernel.resize(m_width * m_height * m_depth);
}

template<typename T>
size_t tkernel<T>::size() const
{
    return m_kernel.size();
}

template<typename T>
glm::length_t tkernel<T>::length()
{
    return kernel_length(T{ });
};

template<typename T>
glm::uint16 tkernel<T>::width() const
{
    return m_width;
}

template<typename T>
glm::uint16 tkernel<T>::height() const
{
    return m_height;
}

template<typename T>
glm::uint16 tkernel<T>::depth() const
{
    return m_depth;
}

template<typename T>
void tkernel<T>::reset()
{
    for (auto & v : m_kernel)
        v = T();
}

template<typename T>
tkernel<T> tkernel<T>::trimed(
    const glm::uint16 width,
    const glm::uint16 height,
    const glm::uint16 depth) const
{
    assert(width  <= m_width);
    assert(height <= m_height);
    assert(depth  <= m_depth);

    auto kernel = tkernel<T>{ width, height, depth };

    for (glm::uint16 r = 0; r < depth; ++r)
        for (glm::uint16 t = 0; t < height; ++t)
            for (glm::uint16 s = 0; s < width; ++s)
                kernel.value(s, t, r) = value(s, t, r);

    return kernel;
}

template<typename T>
auto tkernel<T>::data() -> decltype(kernel_ptr<T>(s_type_workaround))
{
    return kernel_ptr(m_kernel);
}

template<typename T>
auto tkernel<T>::data() const -> const decltype(kernel_ptr<T>(s_type_workaround))
{
    return kernel_ptr(m_kernel);
}

template<typename T>
T & tkernel<T>::operator[](const size_t i)
{
    assert(i < m_kernel.size());
    return m_kernel[i];
}

template<typename T>
const T & tkernel<T>::operator[](const size_t i) const
{
    assert(i < m_kernel.size());
    return m_kernel[i];
}

template<typename T>
T & tkernel<T>::value(
    const glm::uint16 s
,   const glm::uint16 t
,   const glm::uint16 r)
{
    return m_kernel[index(s, t, r)];
}

template<typename T>
const T & tkernel<T>::value(
    const glm::uint16 s
,   const glm::uint16 t
,   const glm::uint16 r) const
{
    return m_kernel[index(s, t, r)];
}

template<typename T>
size_t tkernel<T>::index(
    const glm::uint16 s
,   const glm::uint16 t
,   const glm::uint16 r) const
{
    assert(s < m_width);
    assert(t < m_height);
    assert(r < m_depth);

    return r * m_width * m_height + t * m_width + s;
}

template<typename T>
template<typename Operator, typename... Args>
void tkernel<T>::for_each(Args&&... args)
{
    static const auto l = length();

    auto d = data();
    const auto s = size();

    #pragma omp parallel for
    for (glm::length_t coefficient = 0; coefficient < l; ++coefficient)
    {
        auto o = Operator(s, coefficient, std::forward<Args>(args)...);

        for (size_t i = 0; i < s; ++i)
            d[i * l + coefficient] = o(i);
    }
}

} // namespace glkernel
