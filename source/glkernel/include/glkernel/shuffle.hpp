#pragma once

#include <glkernel/shuffle.h>

#include <cassert>
#include <vector>
#include <set>
#include <random>
#include <algorithm>

#include <glkernel/glm_compatability.h>


namespace glkernel
{

namespace shuffle
{

std::vector<std::vector<size_t>> unique_index_permutations(
    const int num_indices, const int num_permutations)
{
    // create a vector that is to be permutated 
    auto permutation = std::vector < size_t > { };
    permutation.resize(num_indices);
    for (int i = 0; i < permutation.size(); ++i)
        permutation[i] = i;
    const auto permutation_reset = permutation;

    auto permutations = std::vector<std::vector<size_t>>{ };
    permutations.resize(num_permutations);

    for (int i = 0; i < num_permutations; ++i)
    {
        std::random_shuffle(permutation.begin(), permutation.end());
        permutations[i] = permutation;
    }

    // ToDo: remove below - this is deterministic, but too slow - suggestion, shuffle randomly until unique was found ...

    // for every sub-kernel, a unique permutation is required
    //auto num_possible_permutations = 1;
    //for (int i = 2; i <= num_indices; ++i)
    //    num_possible_permutations *= i;

    //assert(num_possible_permutations >= num_permutations);

    // randomly select permutations by an index: create a list of all possible 
    // permutation indices, shuffle, then select first num_subkernel indices ...

    //auto permutation_indices = std::vector < int > { };
    //permutation_indices.resize(num_possible_permutations);

    //for (int i = 0; i < num_possible_permutations; ++i)
    //    permutation_indices[i] = i;

    //std::random_shuffle(permutation_indices.begin(), permutation_indices.end());

    //// for the first num_subkernel permutation indices create/select the actual permutated lists
    //for (int index = 0, i = 0; i < num_permutations; ++i)
    //{
    //    if (permutation_indices[i] < index) // restart if index was already passed ...
    //    {
    //        permutation = permutation_reset;
    //        index = 0;
    //    }

    //    // select the nth permutation by applying n times next_permutation
    //    bool greater = false;
    //    while (index != permutation_indices[i])
    //    {
    //        greater = std::next_permutation(permutation.begin(), permutation.end());
    //        assert(greater);
    //        ++index;
    //    }
    //    permutations[i] = permutation;
    //}

    return permutations;
}


template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
void bucket_permutate(tkernel<T> & kernel, const glm::uint16 subkernel_width, const glm::uint16 subkernel_height, const glm::uint16 subkernel_depth)
{
    assert(subkernel_width > 0);
    assert(subkernel_height > 0);
    assert(subkernel_depth > 0);

    assert(subkernel_width <= kernel.width());
    assert(subkernel_height <= kernel.height());
    assert(subkernel_depth <= kernel.depth());

    assert(kernel.width() % subkernel_width == 0);
    assert(kernel.height() % subkernel_height == 0);
    assert(kernel.depth() % subkernel_depth == 0);

    // the number of the elements required to fill a sub-kernel is the number of required buckets
    const auto num_buckets = subkernel_width * subkernel_height * subkernel_depth;
    assert(kernel.size() % num_buckets == 0);

    // the number of sub-kernels is also the number of values per bucket
    const auto num_subkernels = static_cast<int>(kernel.size() / num_buckets);

    const auto permutations = unique_index_permutations(num_buckets, num_subkernels);

    // create buckets by sequentially adding every kernel index and shuffling every
    // bucket individually to "randomly" pop back from later on ...
    auto buckets = std::vector<std::vector<size_t>>{ };
    buckets.resize(num_buckets);

    auto index = 0;
    for (int b = 0; b < buckets.size(); ++b)
    {
        for (int i = 0; i < num_subkernels; ++i)
            buckets[b].push_back(index++);

        std::random_shuffle(buckets[b].begin(), buckets[b].end());
    }

    // use permutations to pop the last item of each bucket, while 
    // selecting the bucket based on the subkernels permutation ...

    auto subkernel_indices = std::vector<size_t>{ };
    subkernel_indices.resize(num_buckets);

    // a copy of the given kernel is used to read and reassign values from
    const auto read_kernel = kernel;

    const auto kw_over_w = kernel.width()  / subkernel_width;
    const auto kh_over_h = kernel.height() / subkernel_height;

    const auto w_step = subkernel_width;
    const auto h_step = subkernel_height * kernel.width();
    const auto d_step = subkernel_depth  * kernel.width() * kernel.height();

    for (int k = 0; k < num_subkernels; ++k)
    {
        const auto offset = w_step * (k % kw_over_w) + h_step * ((k / kw_over_w) % kh_over_h) + d_step * (k / (kw_over_w * kh_over_h));

        // retrieve indices to map subkernel indices to the given kernel
        auto i = 0;
        for (int d = 0; d < subkernel_depth;  ++d)
        for (int h = 0; h < subkernel_height; ++h)
        for (int w = 0; w < subkernel_width; ++w)
            subkernel_indices[i++] = offset + d * kernel.width() * kernel.height() + h * kernel.width() + w;

        for (int i_permutation = 0; i_permutation < num_buckets; ++i_permutation)
        {
            const auto i_bucket = permutations[k][i_permutation];
            const auto i_read   = buckets[i_bucket].back();
            const auto i_kernel = subkernel_indices[i_permutation];

            kernel[i_kernel] = read_kernel[i_read];

            buckets[i_bucket].pop_back();
        }
    }
}


} // namespace shuffle

} // namespace glkernel
