#pragma once

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
struct tkernel
{
    tkernel(glm::uint16 width = 1, glm::uint16 height = 1, glm::uint16 depth = 1);

    size_t size() const;

    glm::uint16 width() const;
    glm::uint16 height() const;
    glm::uint16 depth() const;

    auto data() const -> decltype(kernel_ptr<T>(std::vector<T>()));

    void reset();

    T & operator[](size_t i);
    const T & operator[](size_t i) const;

    T & value(glm::uint16 s = 0, glm::uint16 t = 0, glm::uint16 r = 0);
    const T & value(glm::uint16 s = 0, glm::uint16 t = 0, glm::uint16 r = 0) const;

    size_t index(glm::uint16 s = 0, glm::uint16 t = 0, glm::uint16 r = 0) const;

    tkernel trimed(glm::uint16 width, glm::uint16 height, glm::uint16 depth) const;

protected:
    glm::uint16 m_width;
    glm::uint16 m_height;
    glm::uint16 m_depth;

    std::vector<T> m_kernel;
};

using kernel1  = tkernel<float>;
using kernel2  = tkernel<glm::vec2>; 
using kernel3  = tkernel<glm::vec3>;
using kernel4  = tkernel<glm::vec4>;

using dkernel1 = tkernel<double>;
using dkernel2 = tkernel<glm::dvec2>;
using dkernel3 = tkernel<glm::dvec3>;
using dkernel4 = tkernel<glm::dvec4>;

} // namespace glkernel

#include <glkernel/kernel.hpp>
