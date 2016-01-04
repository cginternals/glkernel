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
*  A random (uniform) sample within each kernel strata is generated.
*
*  This generates uniform sampled positions within each kernel cell:
*  within each stratum a uniform distribution is used. As a result, 
*  each kernel value comprises a position that is located within its
*  stratum. E.g., a kernel2{2, 4} would comprise random positions, 
*  covering 8 strata. The position of value(0, 0) would reside within
*  [0.0, 0.5] for x and [0.0, 0.25] for y.
*
*  Stratified sampling reduces clustering of samples, non-uniform 
*  sampling of areas (e.g., relevant to preserve smaller details).
*
*  @param[in,out] kernel
*  The kernel to be modified, dimensions are used for number of strata
*/
template <typename T, glm::precision P>
void stratified(tkernel<glm::tvec2<T, P>> & kernel);

} // namespace sample

} // namespace glkernel

#include <glkernel/sample.hpp>
