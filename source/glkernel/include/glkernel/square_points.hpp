#pragma once

#include <glkernel/square_points.hpp>

#include <cassert>
#include <random>


namespace glkernel
{

template <typename T, glm::precision P>
size_t square_points_poisson(Kernel<glm::tvec2<T, P>> & kernel, const unsigned int num_probes)
{
    assert(kernel.depth() == 1);

    const T min_dist = 1 / sqrt(static_cast<T>(kernel.size() * sqrt(2)));
    return square_points_poisson(kernel, min_dist, num_probes);
}


template <typename T, glm::precision P>
size_t square_points_poisson(Kernel<glm::tvec2<T, P>> & kernel, const T min_dist, const unsigned int num_probes)
{
    assert(kernel.depth() == 1);

    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::uniform_real_distribution<T> distribute(0.0, 1.0);

    // optimization grid for identifying adjacent points
    class OccupancyMask
    {
    public:
        OccupancyMask(const T min_dist)
        : m_none{ static_cast<size_t>(-1) }
        , m_side{ static_cast<size_t>(ceil(sqrt(2.0) / min_dist)) }
        , m_dist(min_dist)
        {
            m_mask.resize(m_side * m_side, m_none);
        }

        void mask(const glm::tvec2<T, P> & point, const size_t k)
        {
            const auto o = static_cast<int>(point.y * m_side) * m_side + static_cast<int>(point.x * m_side);

            assert(m_mask[o] == m_none);

            m_mask[o] = k;
        }

        bool masked(const glm::tvec2<T, P> & probe, const Kernel<glm::tvec2<T, P>> & kernel) const
        {
            const auto x = static_cast<int>(probe.x * m_side);
            const auto y = static_cast<int>(probe.y * m_side);
            const auto s = static_cast<int>(m_side);

            for (int j = glm::max(0, y - 2); j < std::min(s, y + 3); ++j)
                for (int i = glm::max(0, x - 2); i < std::min(s, x + 3); ++i)
                {
                    const auto o = m_mask[j * m_side + i];
                    if (o != m_none && glm::distance(kernel[o], probe) < m_dist)
                        return true;
                }

            return false;
        }

    protected:
        size_t m_none;

        size_t m_side;
        T m_dist;

        std::vector<size_t> m_mask;
    };

    auto occupancy = OccupancyMask { min_dist };

    size_t k = 0; // number of valid/final points within the kernel
    kernel[k] = glm::tvec2<T, P>(distribute(generator), distribute(generator));

    auto active = std::vector<size_t>();
    active.push_back(k);

    occupancy.mask(kernel[k], k);

    while(!active.empty() && k < kernel.size() - 1)
    {
        const auto point = kernel[active.back()];
        active.pop_back();

        for (unsigned int i = 0; i < num_probes; ++i)
        {
            const auto r = min_dist * (1.0 + distribute(generator)); // radius
            const auto a = T(2.0) * glm::pi<T>() * distribute(generator);  // angle

            const auto probe = glm::vec2{ point.x + r * cos(a), point.y + r * sin(a) };

            // within square?
            if (probe.x < 0.0 || probe.x > 1.0 || probe.y < 0.0 || probe.y > 1.0)
                continue;

            // points within min_dist?
            if (occupancy.masked(probe, kernel))
                continue;

            kernel[++k] = probe;
            active.push_back(k);

            occupancy.mask(probe, k);

            if (k >= kernel.size() - 1)
                break;
        }
    }

    return k;
}

} // namespace glkernel
