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
: m_extent { w, h, d }
{
    m_kernel.resize(w * h * d);
}

template<typename T>
tkernel<T>::tkernel(const glm::u16vec3 & extent)
: tkernel{ extent.x, extent.y, extent.z }
{
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
const glm::u16vec3 & tkernel<T>::extent() const
{
    return m_extent;
}

template<typename T>
glm::uint16 tkernel<T>::width() const
{
    return m_extent.x;
}

template<typename T>
glm::uint16 tkernel<T>::height() const
{
    return m_extent.y;
}

template<typename T>
glm::uint16 tkernel<T>::depth() const
{
    return m_extent.z;
}

template<typename T>
void tkernel<T>::reset()
{
    for (auto & v : m_kernel)
        v = T();
}

template<typename T>
tkernel<T> tkernel<T>::trimmed(
    const glm::uint16 width,
    const glm::uint16 height,
    const glm::uint16 depth) const
{
    assert(width  <= m_extent[0]);
    assert(height <= m_extent[1]);
    assert(depth  <= m_extent[2]);

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
    assert(s < m_extent[0]);
    assert(t < m_extent[1]);
    assert(r < m_extent[2]);

    return r * m_extent[0] * m_extent[1] + t * m_extent[0] + s;
}

template<typename T>
glm::u16vec3 tkernel<T>::position(const size_t index) const
{
    assert(index < size());

    const auto wh = m_extent[0] * m_extent[1];

    auto pos = glm::u16vec3{ 0, 0, 0 };
    pos[2] = static_cast<glm::uint16>(index / wh);
    pos[1] = static_cast<glm::uint16>(index % wh / m_extent[0]);
    pos[0] = static_cast<glm::uint16>(index % m_extent[0]);

    return pos;
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

template<typename T>
template<typename Operator, typename... Args>
void tkernel<T>::for_each_position(Args&&... args)
{
    static const auto l = length();

    auto d = data();
    const auto s = size();

    #pragma omp parallel for
    for (glm::length_t coefficient = 0; coefficient < l; ++coefficient)
    {
        auto o = Operator(extent(), coefficient, std::forward<Args>(args)...);

        for (size_t i = 0; i < s; ++i)
            d[i * l + coefficient] = o(position(i));
    }
}


} // namespace glkernel
