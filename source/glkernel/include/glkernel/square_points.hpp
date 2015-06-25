#pragma once

#include <glkernel/square_points.hpp>

#include <cassert>
#include <random>
#include <vector>
#include <list>
#include <iterator>

#include <glkernel/glm_compatability.h>


namespace glkernel
{

namespace
{
    // optimization grid for identifying adjacent points

    template <typename T, glm::precision P>
    class PoissonDiskOccupancyMap
    {
    public:
        PoissonDiskOccupancyMap(const T min_dist)
            : m_none{ static_cast<size_t>(-1) }
            , m_side{ static_cast<size_t>(std::ceil(sqrt(2.0) / min_dist)) }
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

            const auto x_min = std::min(s, x + 3);
            const auto y_min = std::min(s, y + 3);

            for (int j = glm::max(0, y - 2); j < y_min; ++j)
                for (int i = glm::max(0, x - 2); i < x_min; ++i)
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
}


template <typename T, glm::precision P>
size_t square_points_poisson(Kernel<glm::tvec2<T, P>> & kernel, const unsigned int num_probes)
{
    assert(kernel.depth() == 1);

    const T min_dist = 1 / sqrt(static_cast<T>(kernel.size() * sqrt(2) * 1.12));
    return square_points_poisson(kernel, min_dist, num_probes);
}


template <typename T, glm::precision P>
size_t square_points_poisson_ext(Kernel<glm::tvec2<T, P>> & kernel, const unsigned int num_probes)
{
    assert(kernel.depth() == 1);

    const T min_dist = 1 / sqrt(static_cast<T>(kernel.size() * sqrt(2) * 0.86));
    return square_points_poisson_ext(kernel, min_dist, num_probes);
}

template <typename T, glm::precision P>
size_t square_points_poisson(Kernel<glm::tvec2<T, P>> & kernel, const T min_dist, const unsigned int num_probes)
{
    assert(kernel.depth() == 1);

    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::uniform_real_distribution<T> distribute(0.0, 1.0);

    auto occupancy = PoissonDiskOccupancyMap<T, P>{ min_dist };

    size_t k = 0; // number of valid/final points within the kernel
    kernel[k] = glm::tvec2<T, P>(0.5, 0.5);

    auto actives = std::vector<size_t>();
    actives.push_back(k);

    occupancy.mask(kernel[k], k);

    while(!actives.empty() && k < kernel.size() - 1)
    {
        const auto active = kernel[actives.back()];
        actives.pop_back();

        for (unsigned int i = 0; i < num_probes; ++i)
        {
            const auto r = min_dist * (1.0 + distribute(generator)); // radius
            const auto a = T(2.0) * glm::pi<T>() * distribute(generator);  // angle

            const auto probe = glm::vec2{ active.x + r * cos(a), active.y + r * sin(a) };

            // within square?
            if (probe.x < 0.0 || probe.x > 1.0 || probe.y < 0.0 || probe.y > 1.0)
                continue;

            // points within min_dist?
            if (occupancy.masked(probe, kernel))
                continue;

            kernel[++k] = probe;
            actives.push_back(k);

            occupancy.mask(probe, k);

            if (k >= kernel.size() - 1)
                break;
        }
    }
    return k;
}

template <typename T, glm::precision P>
size_t square_points_poisson_ext(Kernel<glm::tvec2<T, P>> & kernel, const T min_dist, const unsigned int num_probes)
{
    assert(kernel.depth() == 1);

    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::uniform_real_distribution<T> distribute(0.0, 1.0);
    std::uniform_int_distribution<> int_distribute(0, std::numeric_limits<int>::max());

    auto occupancy = PoissonDiskOccupancyMap<T, P>{ min_dist };

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

        // pick nearest probe from sample set
        glm::vec2 nearest_probe;
        auto nearest_dist = 2.0 * min_dist;
        auto nearest_found = false;

        for (unsigned int i = 0; i < num_probes; ++i)
        {
            // probes position bias towards min_dist
            const auto r = min_dist * (1.0 + distribute(generator) * static_cast<T>(i) / num_probes); // radius
            const auto a = T(2.0) * glm::pi<T>() * distribute(generator);  // angle

            const auto probe = glm::vec2{ active.x + r * cos(a), active.y + r * sin(a) };

            // within square?
            if (probe.x < 0.0 || probe.x > 1.0 || probe.y < 0.0 || probe.y > 1.0)
                continue;

            // points within min_dist?
            if (occupancy.masked(probe, kernel))
                continue;

            // is this nearest point yet?
            const auto new_dist = glm::distance(probe, active);
            if (nearest_dist < new_dist)
                continue;

            if (!nearest_found)
                nearest_found = true;

            nearest_dist = new_dist;
            nearest_probe = probe;
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
    return k;
}

} // namespace glkernel
