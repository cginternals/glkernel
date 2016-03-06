#pragma once

#include <glkernel/sort.h>

#include <algorithm>

#include <glkernel/glm_compatability.h>


namespace glkernel
{

namespace sort
{

template <typename T, glm::precision P, template<typename, glm::precision> class V>
struct distance_comparator
{
    distance_comparator(const V<T, P>& origin)
    : m_origin {origin}
    {
    }

    bool operator()(const V<T, P>& a, const V<T, P>& b) const
    {
        return glm::distance(a, m_origin) < glm::distance(b, m_origin);
    }

private:
    V<T, P> m_origin;
};

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void distance(tkernel<V<T, P>> & kernel, const V<T, P> & origin)
{
    const distance_comparator<T, P, V> comparator {origin};
    std::sort(kernel.begin(), kernel.end(), comparator);
}


} // namespace sort

} // namespace glkernel
