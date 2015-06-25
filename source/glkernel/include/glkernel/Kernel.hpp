#pragma once

#include <glkernel/Kernel.h>

#include <cassert>
#include <type_traits>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/gtc/type_ptr.hpp>


namespace glkernel
{

template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
const T * kernel_ptr(const std::vector<T> & kernel)
{
    return kernel.data();
}

template<typename T, typename std::enable_if<std::is_same<T, glm::vec2>::value, int>::type = 0>
const typename T::value_type * kernel_ptr(const std::vector<T> & kernel)
{
    return glm::value_ptr(kernel.front());
}

template<typename T, typename std::enable_if<std::is_same<T, glm::vec3>::value, int>::type = 0>
const typename T::value_type * kernel_ptr(const std::vector<T> & kernel)
{
    return glm::value_ptr(kernel.front());
}

template<typename T, typename std::enable_if<std::is_same<T, glm::vec4>::value, int>::type = 0>
const typename T::value_type * kernel_ptr(const std::vector<T> & kernel)
{
    return glm::value_ptr(kernel.front());
}

template<typename T, typename std::enable_if<std::is_same<T, glm::dvec2>::value, int>::type = 0>
const typename T::value_type * kernel_ptr(const std::vector<T> & kernel)
{
    return glm::value_ptr(kernel.front());
}

template<typename T, typename std::enable_if<std::is_same<T, glm::dvec3>::value, int>::type = 0>
const typename T::value_type * kernel_ptr(const std::vector<T> & kernel)
{
    return glm::value_ptr(kernel.front());
}

template<typename T, typename std::enable_if<std::is_same<T, glm::dvec4>::value, int>::type = 0>
const typename T::value_type * kernel_ptr(const std::vector<T> & kernel)
{
    return glm::value_ptr(kernel.front());
}


template<typename T>
Kernel<T>::Kernel(const glm::uint16 width, const glm::uint16 height, const glm::uint16 depth)
: m_width { width  }
, m_height{ height }
, m_depth { depth  }
{
    m_kernel.resize(m_width * m_height * m_depth);
}

template<typename T>
size_t Kernel<T>::size() const
{
    return m_kernel.size();
}

template<typename T>
glm::uint16 Kernel<T>::width() const
{
    return m_width;
}

template<typename T>
glm::uint16 Kernel<T>::height() const
{
    return m_height;
}

template<typename T>
glm::uint16 Kernel<T>::depth() const
{
    return m_depth;
}

template<typename T>
auto Kernel<T>::values() const -> decltype(kernel_ptr<T>(std::vector<T>()))
{
    return kernel_ptr(m_kernel);
}

template<typename T>
T & Kernel<T>::operator[](const size_t i)
{
    assert(i < m_kernel.size());
    return m_kernel[i];
}

template<typename T>
const T & Kernel<T>::operator[](const size_t i) const
{
    assert(i < m_kernel.size());
    return m_kernel[i];
}

template<typename T>
T & Kernel<T>::value(glm::uint16 s = 0, glm::uint16 t = 0, glm::uint16 u = 0)
{
    return m_kernel[index(s, t, u)];
}

template<typename T>
const T & Kernel<T>::value(const glm::uint16 s = 0, const glm::uint16 t = 0, const glm::uint16 u = 0) const
{
    return m_kernel[index(s, t, u)];
}

template<typename T>
size_t Kernel<T>::index(const glm::uint16 s = 0, const glm::uint16 t = 0, const glm::uint16 u = 0) const
{
    assert(s < m_width);
    assert(t < m_height);
    assert(u < m_depth);

    return u * m_width * m_height + t * m_width + s;
}

} // namespace glkernel
