#pragma once

#include <glkernel/glkernel_api.h>

#include <vector>

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
    Kernel(glm::uint16 width = 1, glm::uint16 height = 1, glm::uint16 depth = 1);

    size_t size() const;

    glm::uint16 width() const;
    glm::uint16 height() const;
    glm::uint16 depth() const;

    auto values() const -> decltype(kernel_ptr<T>(std::vector<T>()));

    void reset();

    T & operator[](size_t i);
    const T & operator[](size_t i) const;

    T & value(glm::uint16 s = 0, glm::uint16 t = 0, glm::uint16 u = 0);
    const T & value(glm::uint16 s = 0, glm::uint16 t = 0, glm::uint16 u = 0) const;

    size_t index(glm::uint16 s = 0, glm::uint16 t = 0, glm::uint16 u = 0) const;

protected:
    glm::uint16 m_width;
    glm::uint16 m_height;
    glm::uint16 m_depth;

    std::vector<T> m_kernel;
};

} // namespace glkernel

#include <glkernel/Kernel.hpp>
