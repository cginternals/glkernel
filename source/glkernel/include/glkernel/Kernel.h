#pragma once

#include <glkernel/glkernel_api.h>

#include <vector>

#include <glm/common.hpp>


namespace glkernel
{

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
