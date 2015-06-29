#pragma once

#include <glkernel/sequence.h>

#include <glkernel/glm_compatability.h>


namespace glkernel
{

template <typename T>
inline void sequence::uniform_base(T * kernel, const size_t size, const T range_min, const T range_max, const size_t step, const size_t offset)
{
    for (int i = 0; i < size; ++i)
        kernel[i * step + offset] = range_min + (range_max - range_min) * i / (size - 1);
}

template <typename T, int C>
inline void sequence::uniform_base(T * kernel, const size_t size, const T range_min, const T range_max)
{
    for (int c = 0; c < C; ++c)
        uniform_base<T>(kernel, size, range_min, range_max, C, c);
}

template <typename T, int C>
inline void sequence::uniform_base(T * kernel, const size_t size, const T * range_min, const T * range_max)
{
    for (size_t c = 0; c < C; ++c)
        uniform_base<T>(kernel, size, range_min[c], range_max[c], C, c);
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type>
void sequence::uniform(tkernel<T> & kernel, const T range_min, const T range_max)
{
    uniform_base<T, 1>(const_cast<T *>(kernel.data()), kernel.size(), range_min, range_max);
}
template <typename T, glm::precision P>
void sequence::uniform(tkernel<glm::tvec2<T, P>> & kernel, const T range_min, const T range_max)
{
    uniform_base<T, 2>(const_cast<T *>(kernel.data()), kernel.size(), range_min, range_max);
}
template <typename T, glm::precision P>
void sequence::uniform(tkernel<glm::tvec3<T, P>> & kernel, const T range_min, const T range_max)
{
    uniform_base<T, 3>(const_cast<T *>(kernel.data()), kernel.size(), range_min, range_max);
}
template <typename T, glm::precision P>
void sequence::uniform(tkernel<glm::tvec4<T, P>> & kernel, const T range_min, const T range_max)
{
    uniform_base<T, 4>(const_cast<T *>(kernel.data()), kernel.size(), range_min, range_max);
}
template <typename T, glm::precision P>
void sequence::uniform(tkernel<glm::tvec2<T, P>> & kernel, const glm::tvec2<T, P> & range_min, const glm::tvec2<T, P> & range_max)
{
    uniform_base<T, 2>(const_cast<T *>(kernel.data()), kernel.size(), glm::value_ptr(range_min), glm::value_ptr(range_max));
}
template <typename T, glm::precision P>
void sequence::uniform(tkernel<glm::tvec3<T, P>> & kernel, const glm::tvec3<T, P> & range_min, const glm::tvec3<T, P> & range_max)
{
    uniform_base<T, 3>(const_cast<T *>(kernel.data()), kernel.size(), glm::value_ptr(range_min), glm::value_ptr(range_max));
}
template <typename T, glm::precision P>
void sequence::uniform(tkernel<glm::tvec4<T, P>> & kernel, const glm::tvec4<T, P> & range_min, const glm::tvec4<T, P> & range_max)
{
    uniform_base<T, 4>(const_cast<T *>(kernel.data()), kernel.size(), glm::value_ptr(range_min), glm::value_ptr(range_max));
}

} // namespace glkernel
