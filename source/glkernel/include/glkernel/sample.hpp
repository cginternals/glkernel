
#pragma once

#include <glkernel/sample.h>

#include <cassert>
#include <random>
#include <vector>
#include <array>
#include <list>
#include <iterator>
#include <tuple>
#include <algorithm>

#include <glkernel/glm_compatability.h>

#include <glm/gtx/norm.hpp>
#include <glm/gtc/constants.hpp>


namespace glkernel
{


namespace sample
{


// optimization grid for identifying adjacent points

template <typename T, glm::precision P>
struct poisson_square_map
{
    poisson_square_map(const T min_dist)
    : m_none{ static_cast<size_t>(-1) }
    , m_side{ static_cast<size_t>(std::ceil(sqrt(2.0) / min_dist)) }
    , m_dist2(min_dist * min_dist)
    {
        m_mask.resize(m_side * m_side, m_none);
    }

    void mask(const glm::tvec2<T, P> & point, const size_t k)
    {
        const auto s = static_cast<int>(m_side);
        const auto o = static_cast<int>(point.y * s) * s + static_cast<int>(point.x * s);

        assert(m_mask[o] == m_none);

        m_mask[o] = k;
    }

    bool masked(const glm::tvec2<T, P> & probe, const tkernel<glm::tvec2<T, P>> & kernel) const
    {
        const auto s = static_cast<int>(m_side);

        const auto x = static_cast<int>(probe.x * s);
        const auto y = static_cast<int>(probe.y * s);

        const auto corners = std::array<int, 4>{ { y - 2, x - 2, y + 2, x + 2 } };

        for (int j = y - 2; j < y + 3; ++j)
            for (int i = x - 2; i < x + 3; ++i)
            {
                // optimization: skip the 4 corner cases, since the fall not within distance anyway ...
                if ((j == corners[0] || j == corners[2]) && (i == corners[1] || i == corners[3])) 
                    continue;

                const auto i_tiled = i < 0 ? i + s : i % s;
                const auto j_tiled = j < 0 ? j + s : j % s;

                const auto o = m_mask[j_tiled * s + i_tiled];
                if (o == m_none)
                    continue;

                auto masking_probe = kernel[o];

                if (i < 0)
                    masking_probe.x -= 1.0;
                else if (i >= s)
                    masking_probe.x += 1.0;

                if (j < 0)
                    masking_probe.y -= 1.0;
                else if (j >= s)
                    masking_probe.y += 1.0;

                // also optimized by using square distance->skipping sqrt
                const auto delta = masking_probe - probe;
                if (glm::dot(delta, delta) < m_dist2)
                    return true;
            }

        return false;
    }

protected:
    size_t m_none;

    size_t m_side;
    T m_dist2;

    std::vector<size_t> m_mask;
};


template <typename T, glm::precision P>
size_t poisson_square(tkernel<glm::tvec2<T, P>> & kernel, const unsigned int num_probes)
{
    assert(kernel.depth() == 1);

    const T min_dist = 1 / sqrt(static_cast<T>(kernel.size() * sqrt(2)));
    return poisson_square(kernel, min_dist, num_probes);
}


template <typename T, glm::precision P>
size_t poisson_square(tkernel<glm::tvec2<T, P>> & kernel, const T min_dist, const unsigned int num_probes)
{
    assert(kernel.depth() == 1);

    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::uniform_real_distribution<> radius_dist(min_dist, min_dist * 2.0);
    std::uniform_real_distribution<> angle_dist(0.0, 2.0 * glm::pi<T>());

    std::uniform_int_distribution<> int_distribute(0, std::numeric_limits<int>::max());

    auto occupancy = poisson_square_map<T, P>{ min_dist };

    size_t k = 0; // number of valid/final points within the kernel
    kernel[k] = glm::tvec2<T, P>(0.5, 0.5);

    auto actives = std::list<size_t>();
    actives.push_back(k);

    occupancy.mask(kernel[k], k);

    while (!actives.empty() && k < kernel.size() - 1)
    {
        // randomly pick an active point
        const auto pick = int_distribute(generator);

        auto pick_it = actives.begin();
        std::advance(pick_it, pick % actives.size());

        const auto active = kernel[*pick_it];


        std::vector<std::tuple<glm::tvec2<T, P>, T>> probes{ num_probes };

        #pragma omp parallel for
        for (int i = 0; i < static_cast<int>(num_probes); ++i)
        {
            const auto r = radius_dist(generator);
            const auto a = angle_dist(generator);

            auto probe = glm::tvec2<T, P>{ active.x + r * cos(a), active.y + r * sin(a) };

            // within square? (tilable)
            if (probe.x < 0.0)
                probe.x += 1.0;
            else if (probe.x >= 1.0)
                probe.x -= 1.0;

            if (probe.y < 0.0)
                probe.y += 1.0;
            else if (probe.y >= 1.0)
                probe.y -= 1.0;

            // Note: do NOT make this optimization
            //if (!tilable && (probe.x < 0.0 || probe.x > 1.0 || probe.y < 0.0 || probe.y > 1.0))
            //    continue;

            // points within min_dist?
            const auto masked = occupancy.masked(probe, kernel);
            const auto delta = glm::abs(active - probe);

            probes[i] = std::make_tuple<glm::tvec2<T, P>, T>(std::move(probe), 
                (masked ? static_cast<T>(-1.0) : glm::dot(delta, delta)));
        }
        
        // pick nearest probe from sample set
        glm::tvec2<T, P> nearest_probe;
        auto nearest_dist = 4 * min_dist * min_dist;
        auto nearest_found = false;

        for (int i = 0; i < static_cast<int>(num_probes); ++i)
        {
            // is this nearest point yet? - optimized by using square distance -> skipping sqrt
            const auto new_dist = std::get<1>(probes[i]);
            if (new_dist < 0.0 || nearest_dist < new_dist)
                continue;

            if (!nearest_found)
                nearest_found = true;

            nearest_dist = new_dist;
            nearest_probe = std::get<0>(probes[i]);
        }

        if (!nearest_found && (actives.size() > 0 || k > 1))
        {
            actives.erase(pick_it);
            continue;
        }

        kernel[++k] = nearest_probe;
        actives.push_back(k);

        occupancy.mask(nearest_probe, k);
    }

    return k + 1;
}

template <typename T, glm::precision P>
void multi_jittered(tkernel<glm::tvec2<T, P>> & kernel, const bool correlated)
{
    assert(kernel.depth() == 1);

    std::random_device RD;
    std::mt19937_64 generator(RD());

    const auto stratum_size = 1.0 / (kernel.width() * kernel.height());
    const auto subcell_width = 1.0 / kernel.width();
    const auto subcell_height = 1.0 / kernel.height();

    std::uniform_real_distribution<> jitter_dist(0.0, stratum_size);

    // create pools of subcell indices
    std::vector<std::vector<int>> column_indices(kernel.width());
    std::vector<std::vector<int>> row_indices(kernel.height());

    // reverse height and width inside subcells
    for (auto y = 0; y < kernel.width(); ++y)
    {
        // use the same shuffle pattern for all rows for correlated shuffling
        if (y != 0 && correlated)
        {
            column_indices[y] = column_indices[0];
            continue;
        }

        // shuffle columns separately to keep n-rooks condition satisfied
        for (auto x = 0; x < kernel.height(); ++x)
        {
            column_indices[y].push_back(x);
        }
        std::random_shuffle(column_indices[y].begin(), column_indices[y].end());
    }
    // reverse height and width inside subcells
    for (auto x = 0; x < kernel.height(); ++x)
    {
        // use the same shuffle pattern for all columns for correlated shuffling
        if (x != 0 && correlated)
        {
            row_indices[x] = row_indices[0];
            continue;
        }

        // shuffle rows separately to keep n-rooks condition satisfied
        for (auto y = 0; y < kernel.width(); ++y)
        {
            row_indices[x].push_back(y);
        }
        std::random_shuffle(row_indices[x].begin(), row_indices[x].end());
    }

    int k = 0;
    #pragma omp parallel for
    for (auto x = 0; x < kernel.width(); ++x)
    {
        for (auto y = 0; y < kernel.height(); ++y)
        {
            // use subcell_positions for shuffled in-cell positions
            const auto x_coord = x * subcell_width + column_indices[x][y] * stratum_size + jitter_dist(generator);
            const auto y_coord = y * subcell_height + row_indices[y][x] * stratum_size + jitter_dist(generator);
            kernel.value(static_cast<glm::uint16>(x), static_cast<glm::uint16>(y)) = glm::tvec2<T, P>(x_coord, y_coord);
            ++k;
        }
    }
}


template <typename T, glm::precision P>
void n_rooks(tkernel<glm::tvec2<T, P>> & kernel)
{
    assert(kernel.depth() == 1);

    const auto stratum_size = 1.0 / kernel.size();
    std::random_device RD;
    std::mt19937_64 generator(RD());
    // use uniform distribution for jittering inside strata
    std::uniform_real_distribution<> jitter_dist(0.0, stratum_size);

    // create pool of column indices and shuffle it
    std::vector<int> columnIndices;
    for (int k = 0; k < static_cast<int>(kernel.size()); ++k)
    {
        columnIndices.push_back(k);
    }
    std::random_shuffle(columnIndices.begin(), columnIndices.end());

    // use columnIndices to shuffle samples in y-direction
    #pragma omp parallel for
    for (int k = 0; k < static_cast<int>(kernel.size()); ++k)
    {
        const auto x_coord = k * stratum_size + jitter_dist(generator);
        const auto y_coord = columnIndices.at(k) * stratum_size + jitter_dist(generator);
        kernel[k] = glm::tvec2<T, P>(x_coord, y_coord);
    }
}

template <typename T>
class stratified_operator
{
public:
    stratified_operator(const glm::u16vec3 & extent, glm::length_t);

    template <typename F, glm::precision P, template<typename, glm::precision> class V>
    stratified_operator(const glm::u16vec3 & extent, glm::length_t coefficient);

    T operator()(const glm::u16vec3 & position);

protected:
    std::mt19937_64 m_generator;
    std::uniform_real_distribution<T> m_distribute;

    const T m_extent_inverse;
    const glm::length_t m_coefficient;
};


template<typename T>
stratified_operator<T>::stratified_operator(const glm::u16vec3 & extent, const glm::length_t coefficient)
: m_generator{ std::random_device{}() }
, m_distribute{ static_cast<T>(0.0), static_cast<T>(1.0) / extent[coefficient] }
, m_extent_inverse{ static_cast<T>(1.0) / extent[coefficient] }
, m_coefficient{ coefficient }
{
}

template <typename T>
template <typename F, glm::precision P, template<typename, glm::precision> class V>
stratified_operator<T>::stratified_operator(const glm::u16vec3 & extent, const glm::length_t coefficient)
: stratified_operator{ extent, coefficient }
{
}

template<typename T>
T stratified_operator<T>::operator()(const glm::u16vec3 & position)
{
    return position[m_coefficient] * m_extent_inverse + m_distribute(m_generator);
}

template <typename T>
void stratified(tkernel<T> & kernel)
{
    // the kernels dimensionality should match its value type,
    // i.e., at least two dimensions should be unused (equal 1)
    assert(kernel.depth() == 1 && kernel.height()  == 1);
    kernel.template for_each_position<stratified_operator<T>>();
}

template <typename T, glm::precision P>
void stratified(tkernel<glm::tvec2<T, P>> & kernel)
{
    // the kernels dimensionality should match its value type,
    // i.e., at least one dimension should be unused (equal 1)
    assert(kernel.depth() == 1);
    kernel.template for_each_position<stratified_operator<T>>();
}

template <typename T, glm::precision P>
void stratified(tkernel<glm::tvec3<T, P>> & kernel)
{
    // the kernels dimensionality should match its value type,
    // i.e., all three dimensions can be used (no assert required)
    kernel.template for_each_position<stratified_operator<T>>();
}
namespace {

// adapted code from "Hammersley Points on the Hemisphere", Holger Dammertz
// http://holger.dammertz.org/stuff/notes_HammersleyOnHemisphere.html
// which is licensed under http://creativecommons.org/licenses/by/3.0/

template <typename T>
T radical_inverse(unsigned int bits)
{
    // the bit order of the number is inversed and interpreted as a float
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return static_cast<T>(bits) * static_cast<T>(2.3283064365386963e-10); // divide by 2^32
}

template <typename T>
T van_der_corput(unsigned int n, const unsigned int base)
{
    if (base == 2)
    {
        return radical_inverse<T>(n);
    }

    const T inverse = 1 / static_cast<T>(base);
    T result = 0;
    for (T inverse_power = inverse; n != 0; inverse_power *= inverse)
    {
        result += (n % base) * inverse_power;
        n /= base;
    }
    return result;
}

template <typename T, glm::precision P>
glm::tvec3<T, P> hemisphere_sample_uniform(const T u, const T v)
{
    const T phi = v * 2 * glm::pi<T>();
    const T cosTheta = 1 - u;
    const T sinTheta = sqrt(1 - cosTheta * cosTheta);
    return glm::tvec3<T, P>{ cos(phi) * sinTheta, sin(phi) * sinTheta, cosTheta };
}

template <typename T, glm::precision P>
glm::tvec3<T, P> hemisphere_sample_cos(const T u, const T v)
{
    const T phi = v * 2 * glm::pi<T>();
    const T cosTheta = sqrt(1 - u);
    const T sinTheta = sqrt(1 - cosTheta * cosTheta);
    return glm::tvec3<T, P>{ cos(phi) * sinTheta, sin(phi) * sinTheta, cosTheta };
}

} // anonymous namespace

template <typename T, glm::precision P>
void hammersley(tkernel<glm::tvec2<T, P>> & kernel)
{
    #pragma omp parallel for
    for (int i = 0; i < static_cast<int>(kernel.size()); ++i)
    {
        const auto u = static_cast<T>(i) / kernel.size();
        const auto v = radical_inverse<T>(i);
        kernel[i] = glm::tvec2<T, P>(u, v);
    }
}

template <typename T, glm::precision P>
void hammersley_sphere(tkernel<glm::tvec3<T, P>> & kernel, const HemisphereMapping type)
{
    #pragma omp parallel for
    for (int i = 0; i < static_cast<int>(kernel.size()); ++i)
    {
        const auto u = static_cast<T>(i) / kernel.size();
        const auto v = radical_inverse<T>(i);
        switch (type)
        {
        case HemisphereMapping::Uniform:
            kernel[i] = hemisphere_sample_uniform<T, P>(u, v);
            break;
        case HemisphereMapping::Cosine:
            kernel[i] = hemisphere_sample_cos<T, P>(u, v);
            break;
        default:
            break;
        }
    }
}

template <typename T, glm::precision P>
void halton(tkernel<glm::tvec2<T, P>> & kernel, const unsigned int base1, const unsigned int base2)
{
    #pragma omp parallel for
    for (int i = 0; i < static_cast<int>(kernel.size()); ++i)
    {
        const auto u = van_der_corput<T>(i, base1);
        const auto v = van_der_corput<T>(i, base2);
        kernel[i] = glm::tvec2<T, P>(u, v);
    }
}

template <typename T, glm::precision P>
void halton_sphere(
    tkernel<glm::tvec3<T, P>> & kernel,
    const unsigned int base1,
    const unsigned int base2,
    const HemisphereMapping type)
{
    #pragma omp parallel for
    for (int i = 0; i < static_cast<int>(kernel.size()); ++i)
    {
        const auto u = van_der_corput<T>(i, base1);
        const auto v = van_der_corput<T>(i, base2);
        switch (type)
        {
        case HemisphereMapping::Uniform:
            kernel[i] = hemisphere_sample_uniform<T, P>(u, v);
            break;
        case HemisphereMapping::Cosine:
            kernel[i] = hemisphere_sample_cos<T, P>(u, v);
            break;
        default:
            break;
        }
    }
}

template <typename T, glm::precision P>
void best_candidate(tkernel<glm::tvec2<T, P>> & kernel, const unsigned int num_candidates)
{
    assert(num_candidates >= 1);

    std::random_device RD;
    std::mt19937_64 generator(RD());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    for (size_t k = 0; k < kernel.size(); ++k)
    {
        std::vector<glm::tvec2<T, P>> candidates(num_candidates);
        std::vector<T> min_dists(num_candidates);
        // generate candidates
        #pragma omp parallel for
        for (int c = 0; c < static_cast<int>(num_candidates); ++c)
        {
            candidates[c] = { dist(generator), dist(generator) };

            // test candidates against previously accepted samples
            T min_squared = 2;
            for (size_t i = 0; i < k; ++i)
            {
                const T dist_squared = glm::length2(candidates[c] - kernel[i]);
                min_squared = std::min(min_squared, dist_squared);
            }
            min_dists[c] = min_squared;
        }

        // find best candidate
        T best_dist = min_dists[0];
        unsigned int best_index = 0;
        for (unsigned int c = 1; c < num_candidates; ++c)
        {
            if (min_dists[c] > best_dist)
            {
                best_dist = min_dists[c];
                best_index = c;
            }
        }

        kernel[k] = candidates[best_index];
    }
}

template <typename T, glm::precision P>
void best_candidate(tkernel<glm::tvec3<T, P>> & kernel, const unsigned int num_candidates)
{
    assert(num_candidates >= 1);

    std::random_device RD;
    std::mt19937_64 generator(RD());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    for (size_t k = 0; k < kernel.size(); ++k)
    {
        std::vector<glm::tvec3<T, P>> candidates(num_candidates);
        std::vector<T> min_dists(num_candidates);
        // generate candidates
        #pragma omp parallel for
        for (int c = 0; c < static_cast<int>(num_candidates); ++c)
        {
            candidates[c] = { dist(generator), dist(generator), dist(generator) };

            // test candidates against previously accepted samples
            T min_squared = 3;
            for (size_t i = 0; i < k; ++i)
            {
                const T dist_squared = glm::length2(candidates[c] - kernel[i]);
                min_squared = std::min(min_squared, dist_squared);
            }
            min_dists[c] = min_squared;
        }

        // find best candidate
        T best_dist = min_dists[0];
        unsigned int best_index = 0;
        for (unsigned int c = 1; c < num_candidates; ++c)
        {
            if (min_dists[c] > best_dist)
            {
                best_dist = min_dists[c];
                best_index = c;
            }
        }

        kernel[k] = candidates[best_index];
    }
}

template <typename T, glm::precision P>
void golden_point_set(tkernel<glm::tvec2<T, P>> & kernel)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::uniform_real_distribution<> rand_dist(0.0, 1.0);

    T x = rand_dist(generator);

    T min = x;
    unsigned int idx = 0;

    // set the first coordinates
    for (unsigned int i = 0; i < kernel.size(); ++i)
    {
        auto& item = kernel[i];

        item.y = x;

        if (x < min)
        {
            min = x;
            idx = i;
        }

        // increment the coordinate by the inverted golden ratio
        x += 0.618033988749894;

        if (x >= 1)
        {
            --x;
        }
    }

    // find the first Fibonacci >= N
    unsigned int f = 1;
    unsigned int fp = 1;
    unsigned int parity = 0;

    while(f + fp < kernel.size())
    {
        unsigned int tmp = f;
        f += fp;
        fp = tmp;

        ++parity;
    }

    // set the increment and decrement
    unsigned int inc = fp;
    unsigned int dec = f;
    
    if (parity & 1)
    {
        inc = f;
        dec = fp;
    }

    // permute the first coordinates
    kernel[0].x = kernel[idx].y;

    for (unsigned int i = 1; i < kernel.size(); ++i)
    {
        if (idx < dec)
        {
            idx += inc;

            if(idx >= kernel.size())
                idx -= dec;
        }
        else
        {
            idx -= dec;
        }

        kernel[i].x = kernel[idx].y;
    }

    // set the initial second coordinate
    T y = rand_dist(generator);

    // set the second coordinates
    for (unsigned int i = 0; i < kernel.size(); ++i)
    {
        kernel[i].y = y;

        // increment the coordinate by the inverted golden ratio
        y += 0.618033988749894;

        if (y >= 1)
        {
            --y;
        }
    }
}

} // namespace sample


} // namespace glkernel
