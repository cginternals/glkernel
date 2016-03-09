#pragma once

#include <glm/gtc/type_precision.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/glm_compatability.h>


namespace glkernel
{

namespace sample
{

//@{
/**
*  @brief
*    Values of the kernel are set to positions using poisson disk sampling.
*
*  @return
*    The number of actual generated points. Note: this number is 
*    between 0 and the kernel's size.
*/

// Guess a good number that targets the actual generated number of 
// points generated to match kernel's size.
template <typename T, glm::precision P>
size_t poisson_square(tkernel<glm::tvec2<T, P>> & kernel, unsigned int num_probes = 32);

// In contrast to the typical default impl. this impl uses the best 
// of num_probes, randomizes the actives, ...
template <typename T, glm::precision P>
size_t poisson_square(tkernel<glm::tvec2<T, P>> & kernel, T min_dist, unsigned int num_probes = 32);
//@}

//@{
/**
*  @brief
*    A random (uniform) sample within each kernel strata is generated.
*
*    This generates uniform sampled positions within each kernel cell:
*    within each stratum a uniform distribution is used. As a result, 
*    each kernel value comprises a position that is located within its
*    stratum. E.g., a kernel2{2, 4} would comprise random positions, 
*    covering 8 strata. The position of value(0, 0) would reside within
*    [0.0, 0.5] for x and [0.0, 0.25] for y.
*
*    Stratified sampling reduces clustering of samples, non-uniform 
*    sampling of areas (e.g., relevant to preserve smaller details).
*
*  @param[in,out] kernel
*    The kernel to be modified, with its extent specifying the number 
*    of strata. Note: the value type should match the kernels extent,
*    e.g., a vec2 kernel should not be used for a kernel of 3d extent.
*/
template <typename T, glm::precision P>
void stratified(tkernel<glm::tvec1<T, P>> & kernel);

/**
*  @brief
*  Generates the hammersley point set
*
*  @param[in,out] kernel
*  The kernel to be modified
*/
template <typename T, glm::precision P>
void hammersley(tkernel<glm::tvec2<T, P>> & kernel);

/**
*  @brief
*  Generates the halton point set
*
*  @param[in,out] kernel
*  The kernel to be modified
*
*  @param[in] base1
*  Base for the "van der Corput" sequence used for the x coordinates
*
*  @param[in] base2
*  Base for the "van der Corput" sequence used for the y coordinates
*/
template <typename T, glm::precision P>
void halton(tkernel<glm::tvec2<T, P>> & kernel, const unsigned int base1, const unsigned int base2);

/**
*  @brief
*  Hemisphere mapping used for hammersley and halton sampling
*/
enum class HemisphereMapping : unsigned char
{
    Uniform,
    Cosine
};

/**
*  @brief
*  Generates the hammersley point set and maps it to a hemisphere
*
*  @param[in,out] kernel
*  The kernel to be modified
*
*  @param[in] type
*  Mapping used for generating points on a sphere
*/
template <typename T, glm::precision P>
void hammersley_sphere(
    tkernel<glm::tvec3<T, P>> & kernel,
    const HemisphereMapping type = HemisphereMapping::Uniform);

/**
*  @brief
*  Generates the halton point set and maps it to a hemisphere
*
*  @param[in,out] kernel
*  The kernel to be modified
*
*  @param[in] type
*  Mapping used for generating points on a sphere
*
*  @param[in] base1
*  Base for the "van der Corput" sequence used for the x coordinates
*
*  @param[in] base2
*  Base for the "van der Corput" sequence used for the y coordinates
*/
template <typename T, glm::precision P>
void halton_sphere(
    tkernel<glm::tvec3<T, P>> & kernel,
    const unsigned int base1,
    const unsigned int base2,
    const HemisphereMapping type = HemisphereMapping::Uniform);
/*
*  @brief
*  Generates several candidates for each samples and selects the one
*  that is farthest to the previously selected samples
*
*  @param[in,out] kernel
*  The kernel to be modified
*
*  @param[in] num_candidates
*  Number of candidates generated for each sample
*/
template <typename T, glm::precision P>
void best_candidate(tkernel<glm::tvec2<T, P>> & kernel, unsigned int num_candidates = 32);
template <typename T, glm::precision P>
void best_candidate(tkernel<glm::tvec3<T, P>> & kernel, unsigned int num_candidates = 32);
template <typename T, glm::precision P>
void stratified(tkernel<glm::tvec2<T, P>> & kernel);

template <typename T, glm::precision P>
void stratified(tkernel<glm::tvec3<T, P>> & kernel);

/**
*  @brief
*  Subdivides pixel area into grid and creates one jiterred sample per row/column
*
*  jittering is done using a uniform distribution
*
*  @param[in,out] kernel
*  The kernel to be modified, size is used for number of samples
*/
template <typename T, glm::precision P>
void n_rooks(tkernel<glm::tvec2<T, P>> & kernel);
//@}
/**
*  @brief
*  Subdivides pixel area into n x m strata with one sample each
*
*  Each stratum is divided into subcells and samples are chosen,
*  so that the n-rooks condition is satisfied for the grid created by the subcells.
*  Reduces clumping on one dimensional projection of pattern in comparison to stratified sampling
*
*  @param[in] correlated
*  Use the same shuffle pattern for all rows/column to reduce sample clumpiness
*
*  @param[in,out] kernel
*  The kernel to be modified, dimensions are used for number of strata
*/
template <typename T, glm::precision P>
void multi_jittered(tkernel<glm::tvec2<T, P>> & kernel, const bool correlated = false);

} // namespace sample

} // namespace glkernel

#include <glkernel/sample.hpp>
