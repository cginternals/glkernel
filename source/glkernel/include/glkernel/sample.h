#pragma once

#include <glm/gtc/type_precision.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/glm_compatability.h>


namespace glkernel
{

namespace sample
{

// returns number of actual generated points (note: this number is between 0 and kernel.size)

// guess a good number that targets the actual generated number of points generated to match kernel.size
template <typename T, glm::precision P>
size_t poisson_square(tkernel<glm::tvec2<T, P>> & kernel, unsigned int num_probes = 32);

// in contrast to the typical default impl. this impl uses the best of num_probes, randomizes the actives, ...
template <typename T, glm::precision P>
size_t poisson_square(tkernel<glm::tvec2<T, P>> & kernel, T min_dist, unsigned int num_probes = 32);

/**
*  @brief
*  Subdivides pixel area into n x m strata with one sample each
*
*  Each stratum is divided into subcells and samples are chosen,
*  so that the n-rooks condition is satisfied for the grid created by the subcells.
*  Reduces clumping on one dimensional projection of pattern in comparison to stratified sampling
*
*  @param[in,out] kernel
*  The kernel to be modified, dimensions are used for number of strata
*/
template <typename T, glm::precision P>
void multi_jittered(tkernel<glm::tvec2<T, P>> & kernel);

} // namespace sample

} // namespace glkernel

#include <glkernel/sample.hpp>
