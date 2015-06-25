#pragma once


#include <random>


namespace glkernel
{

template <typename T, glm::precision P>
void square_points_poisson(Kernel<glm::tvec2<T, P>> & kernel, const T min_dist, const unsigned int num_probes = 30);

} // namespace glkernel

#include <glkernel/square_points.hpp>
