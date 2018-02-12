#pragma once

#include <glkernel/Kernel.h>
#include <glm/gtc/type_precision.hpp>
#include <glkernel/noise.h>


namespace glkernel
{




namespace noise
{


template<typename T1, typename T2, typename T3>
void uniform(tkernel<T1> &, const T2, const T3);

template <typename T1, typename T2, typename T3,
          glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<V<T1, P>> &, const T2, const T3);

template <typename T1, typename T2, typename T3,
          glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2, template<typename, glm::precision> class V3>
void uniform(tkernel<V1<T1, P>> &, const V2<T2, P> &, const V3<T3, P> &);


template<typename T1, typename T2, typename T3>
void normal(tkernel<T1> &, const T2, const T3);

template <typename T1, typename T2, typename T3,
          glm::precision P, template<typename, glm::precision> class V>
void normal(tkernel<V<T1, P>> &, const T2, const T3);

template <typename T1, typename T2, typename T3,
          glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2, template<typename, glm::precision> class V3>
void normal(tkernel<V1<T1, P>> &, const V2<T2, P> &, const V3<T3, P> &);


template <typename T, glm::precision P, template<typename, glm::precision> class V>
void gradient(tkernel<V<T, P>> &
    , const GradientNoiseType = GradientNoiseType::Perlin
    , const OctaveType = OctaveType::Standard
    , const unsigned int = 3
    , const unsigned int = 5);


} // namespace noise


namespace sample
{


//template <typename T, glm::precision P>
//size_t poisson_square(tkernel<glm::tvec2<T, P>> & kernel, unsigned int num_probes = 32);

template <typename T>
void poisson_square(tkernel<T> &, const unsigned int = 32);

template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void poisson_square(tkernel<V<T, P>> &, const unsigned int = 32);




template <typename T1, typename T2>
void poisson_square(tkernel<T1> &, const T2, const unsigned int = 32);

template <typename T1, typename T2,
          glm::precision P, template<typename, glm::precision> class V>
void poisson_square(tkernel<V<T1, P>> &, const T2, const unsigned int = 32);




template <typename T1, typename T2,
          glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
size_t poisson_square(tkernel<V1<T1, P>> &, const V2<T2, P> &, const unsigned int = 32);

template <typename T1, typename T2,
          glm::precision P, template<typename, glm::precision> class V>
size_t poisson_square(tkernel<T1> &, const V<T2, P> &, const unsigned int = 32);






//template <typename T, glm::precision P>
//size_t poisson_square(tkernel<glm::tvec2<T, P>> & kernel, T min_dist, unsigned int num_probes = 32);


} // namespace sample


namespace scale
{



} // namespace scale


namespace sequence
{


} // namespace sequence


namespace shuffle
{



} // namespace shuffle


namespace sort
{



} // namespace sort




} // namespace glkernel


#include "glkernel_generalizations.cpp"
