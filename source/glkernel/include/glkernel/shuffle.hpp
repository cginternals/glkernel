#pragma once

#include <glkernel/shuffle.h>

#include <cassert>
#include <vector>
#include <set>
#include <random>
#include <algorithm>
#include <array>
#include <ctime>

#include <glkernel/glm_compatability.h>


namespace glkernel
{

namespace shuffle
{

struct abstract_permutations
{
    virtual size_t operator()(const size_t bucket, const size_t permutation) const = 0;
    virtual ~abstract_permutations() {};
};
  
struct unique_index_permutations : abstract_permutations
{
    unique_index_permutations(const int num_indices, const int num_permutations)
    {
        // create a vector that is to be permutated 
        auto permutation = std::vector < size_t > { };
        permutation.resize(num_indices);
        for (int i = 0; i < num_indices; ++i)
            permutation[i] = i;
        const auto permutation_reset = permutation;

        m_permutations.resize(num_permutations);

        for (int i = 0; i < num_permutations; ++i)
        {
            std::random_shuffle(permutation.begin(), permutation.end());
            m_permutations[i] = permutation;
        }
    }

    size_t operator()(const size_t bucket, const size_t permutation) const
    {
        return m_permutations[bucket][permutation];
    }

protected:
    std::vector<std::vector<size_t>> m_permutations;
};

struct static_index_permutation : abstract_permutations
{
    static_index_permutation(const int num_indices)
    {
        m_permutation.resize(num_indices);
        for (int i = 0; i < num_indices; ++i)
            m_permutation[i] = i;

        std::random_shuffle(m_permutation.begin(), m_permutation.end());
    }

    size_t operator()(const size_t, const size_t permutation) const
    {
        return m_permutation[permutation];
    }

protected:
    std::vector<size_t> m_permutation;
};


template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
void bucket_permutate(tkernel<T> & kernel
    , const glm::uint16 subkernel_width
    , const glm::uint16 subkernel_height
    , const glm::uint16 subkernel_depth
    , const bool permutate_per_bucket)
{
    assert(subkernel_width  > 0);
    assert(subkernel_height > 0);
    assert(subkernel_depth  > 0);

    assert(subkernel_width  <= kernel.width());
    assert(subkernel_height <= kernel.height());
    assert(subkernel_depth  <= kernel.depth());

    assert(kernel.width()  % subkernel_width  == 0);
    assert(kernel.height() % subkernel_height == 0);
    assert(kernel.depth()  % subkernel_depth  == 0);

    // the number of the elements required to fill a sub-kernel is the number of required buckets
    const auto num_buckets = subkernel_width * subkernel_height * subkernel_depth;
    assert(kernel.size() % num_buckets == 0);

    if (num_buckets == 0)
        return;

    std::srand(static_cast<unsigned int>(std::time(0)));

    // the number of sub-kernels is also the number of values per bucket
    const auto num_subkernels = static_cast<int>(kernel.size() / num_buckets);

    // create buckets by sequentially adding every kernel index and shuffling every
    // bucket individually to "randomly" pop back from later on ...
    auto buckets = std::vector<std::vector<size_t>>{ };
    buckets.resize(num_buckets);

    auto index = 0;
    for (size_t b = 0; b < buckets.size(); ++b)
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


    // create permutations (or use single, static permutation)
    abstract_permutations * permutations{ nullptr };
    if (permutate_per_bucket)
        permutations = new unique_index_permutations{ num_buckets, num_subkernels };
    else
        permutations = new static_index_permutation{ num_buckets };


    for (int k = 0; k < num_subkernels; ++k)
    {
        const auto offset = w_step * (k % kw_over_w) 
            + h_step * ((k / kw_over_w) % kh_over_h) + d_step * (k / (kw_over_w * kh_over_h));

        // retrieve indices to map subkernel indices to the given kernel
        auto i = 0;
        for (int d = 0; d < subkernel_depth;  ++d)
        for (int h = 0; h < subkernel_height; ++h)
        for (int w = 0; w < subkernel_width; ++w)
            subkernel_indices[i++] = offset + d * kernel.width() * kernel.height() + h * kernel.width() + w;

        for (int i_permutation = 0; i_permutation < num_buckets; ++i_permutation)
        {
            const auto i_bucket = (*permutations)(k, i_permutation);
            const auto i_read   = buckets[i_bucket].back();
            const auto i_kernel = subkernel_indices[i_permutation];

            kernel[i_kernel] = read_kernel[i_read];

            buckets[i_bucket].pop_back();
        }
    }
    delete permutations;
    permutations = nullptr;
}




template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
void bayer(tkernel<T> & kernel)
{
    static const auto bayer2 = std::array<size_t, 4>({ {
         1,  3,
         4,  2 } });

    static const auto bayer3 = std::array<size_t, 9>({ {
         3,  7,  4,
         6,  1,  9, 
         2,  8,  5 } });

    static const auto bayer4 = std::array<size_t, 16>({ {
         1,  9,  3, 11,
        13,  5, 15,  7,
         4, 12,  2, 10,
        16,  8, 14,  6 } });

    static const auto bayer8 = std::array<size_t, 64>({ {
         1, 49, 13, 61,  4, 52, 16, 64, 
        33, 17, 45, 29, 36, 20, 48, 32, 
         9, 57,  5, 53, 12, 60,  8, 56, 
        41, 25, 37, 21, 44, 28, 40, 24, 
         3, 51, 15, 63,  2, 50, 14, 62, 
        35, 19, 47, 31, 34, 18, 46, 30, 
        11, 59,  7, 55, 10, 58,  6, 54, 
        43, 27, 39, 23, 42, 26, 38, 22 } });

    const auto size = kernel.size();
    if (size != 4 && size != 9 && size != 16 && size != 64)
        return;

    // a copy of the given kernel is used to read and reassign values from
    const auto read_kernel = kernel;

    switch (kernel.size())
    {
    case  4:
        for (size_t i = 0; i <  4; ++i)
            kernel[i] = read_kernel[bayer2[i] - 1];
        break;

    case  9:
        for (size_t i = 0; i < 9; ++i)
            kernel[i] = read_kernel[bayer3[i] - 1];
        break;

    case 16:
        for (size_t i = 0; i < 16; ++i)
            kernel[i] = read_kernel[bayer4[i] - 1];
        break;

    case 64:
        for (size_t i = 0; i < 64; ++i)
            kernel[i] = read_kernel[bayer8[i] - 1];
        break;
    }
}

template<typename T>
void random(tkernel<T> & kernel)
{
    std::random_shuffle(kernel.begin(), kernel.end());
}

} // namespace shuffle

} // namespace glkernel
