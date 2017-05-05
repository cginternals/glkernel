
#pragma once

#include <glkernel/sort.h>

#include <algorithm>

#include <glkernel/glm_compatability.h>


namespace glkernel
{


namespace sort
{


template <typename T>
struct distance_comparator
{
    distance_comparator(const T& origin)
    : m_origin {origin}
    {
    }

    bool operator()(const T& a, const T& b) const
    {
        return glm::distance(a, m_origin) < glm::distance(b, m_origin);
    }

private:
    T m_origin;
};

template <typename T>
void distance(tkernel<T> & kernel, const T & origin)
{
    const distance_comparator<T> comparator {origin};
    std::sort(kernel.begin(), kernel.end(), comparator);
}


} // namespace sort


} // namespace glkernel
