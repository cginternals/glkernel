#pragma once

#include <glkernel/glkernel_api.h>

#include <cassert>
#include <vector>
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
class Kernel
{
public:
    Kernel(
        uint16_t width  = 1
    ,   uint16_t height = 1
    ,   uint16_t depth  = 1
    )
    : m_width { width }
    , m_height{ height }
    , m_depth { depth }
    {
        m_kernel.resize(m_width * m_height * m_depth);
    }

    size_t size() const
    {
        return m_kernel.size();
    }

    auto data() const -> decltype(kernel_ptr<T>(std::vector<T>()))
    {
        return kernel_ptr(m_kernel);
    }

    T & operator[](const unsigned int i)
    {
        assert(i < m_kernel.size());
        return m_kernel[i];
    }

    const T & operator[](const unsigned int i) const
    {
        assert(i < m_kernel.size());
        return m_kernel[i];
    }

    T & element(uint16_t s = 0, uint16_t t = 0, uint16_t u = 0)
    {
        return m_kernel[index(s, t, u)];
    }

    const T & element(uint16_t s = 0, uint16_t t = 0, uint16_t u = 0) const
    {
        return m_kernel[index(s, t, u)];
    }

    size_t index(uint16_t s = 0, uint16_t t = 0, uint16_t u = 0) const
    {
        assert(s < m_width);
        assert(t < m_height);
        assert(u < m_depth);

        return u * m_width * m_height + t * m_width + s;
    }

protected:
    uint16_t m_width;
    uint16_t m_height;
    uint16_t m_depth;

    std::vector<T> m_kernel;
};

} // namespace glkernel
