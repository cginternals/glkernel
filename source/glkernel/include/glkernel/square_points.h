#pragma once

#include <random>


namespace glkernel
{

// returns number of actual generated points (note: this number is between 0 and kernel.size)

template <typename T, glm::precision P>
size_t square_points_poisson(Kernel<glm::tvec2<T, P>> & kernel, const unsigned int num_probes = 100);

template <typename T, glm::precision P>
size_t square_points_poisson(Kernel<glm::tvec2<T, P>> & kernel, const T min_dist, const unsigned int num_probes = 100);

} // namespace glkernel

#include <glkernel/square_points.hpp>
