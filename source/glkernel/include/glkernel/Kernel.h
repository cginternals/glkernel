
#pragma once

#include <vector>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/ext/scalar_uint_sized.hpp>


namespace glkernel
{


template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
T * kernel_ptr(std::vector<T> & kernel);

template <typename T, typename std::enable_if<!std::is_floating_point<T>::value>::type * = nullptr>
typename T::value_type * kernel_ptr(std::vector<T> & kernel);


template<typename T>
struct tkernel
{
private:
    static std::vector<T> s_type_workaround;

public:

    tkernel(glm::uint16 width = 1, glm::uint16 height = 1, glm::uint16 depth = 1);
    tkernel(const glm::u16vec3 & extent);

    static glm::length_t length();
    size_t size() const;

    const glm::u16vec3 & extent() const;
    glm::uint16 width() const;
    glm::uint16 height() const;
    glm::uint16 depth() const;

    void reset();

    size_t index(glm::uint16 s = 0, glm::uint16 t = 0, glm::uint16 r = 0) const;
    glm::u16vec3 position(const size_t index) const;

    T & operator[](size_t i);
    const T & operator[](size_t i) const;

    T & value(glm::uint16 s = 0, glm::uint16 t = 0, glm::uint16 r = 0);
    const T & value(glm::uint16 s = 0, glm::uint16 t = 0, glm::uint16 r = 0) const;

    auto data() -> decltype(kernel_ptr<T>(s_type_workaround));
    auto data() const -> const decltype(kernel_ptr<T>(s_type_workaround));

    auto begin() -> decltype(s_type_workaround.begin());
    auto cbegin() const -> decltype(s_type_workaround.cbegin());

    auto end() -> decltype(s_type_workaround.end());
    auto cend() const -> decltype(s_type_workaround.cend());

    auto begin() const -> decltype(s_type_workaround.cbegin());
    auto end() const -> decltype(s_type_workaround.cend());

    tkernel trimmed(glm::uint16 width, glm::uint16 height, glm::uint16 depth) const;

    // index passed to operator (size and coefficient to operator constructor)
    template<typename Operator, typename... Args>
    void for_each(Args&&... args);

    // position passed to operator (extent and coefficient to operator constructor)
    template<typename Operator, typename... Args>
    void for_each_position(Args&&... args);

    // element passed to operator (extent and coefficient to operator constructor)
    template<typename Operator, typename... Args>
    void for_each_element(Args&&... args);

protected:
    std::vector<T> m_kernel;
    glm::u16vec3 m_extent;
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


#include <glkernel/Kernel.hpp>
