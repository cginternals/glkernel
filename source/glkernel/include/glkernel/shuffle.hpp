#pragma once

#include <glkernel/shuffle.h>

#include <cassert>

#include <glkernel/glm_compatability.h>


namespace glkernel
{

template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
void shuffle::bucket_permutate(tkernel<T> & kernel, const glm::uint16 width, const glm::uint16 height, const glm::uint16 depth)
{
    assert(width  > 0);
    assert(height > 0);
    assert(depth  > 0);

    assert(width  <= kernel.width());
    assert(height <= kernel.height());
    assert(depth  <= kernel.depth());

    assert(width  % kernel.width()  == 0);
    assert(height % kernel.height() == 0);
    assert(depth  % kernel.depth()  == 0);

    const auto num_buckets = width * height * depth;

    assert(kernel.size() % num_buckets == 0);
}

} // namespace glkernel
