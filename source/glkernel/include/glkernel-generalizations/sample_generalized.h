#pragma once

#include <glkernel/Kernel.h>

#include <glm/gtc/type_precision.hpp>
#include <glkernel/sample.h>


namespace glkernel
{


namespace sample
{


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
void poisson_square(tkernel<V1<T1, P>> &, const V2<T2, P> &, const unsigned int = 32);

template <typename T1, typename T2,
          glm::precision P, template<typename, glm::precision> class V>
void poisson_square(tkernel<T1> &, const V<T2, P> &, const unsigned int = 32);




template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void stratified(tkernel<V<T, P>> &);




template <typename T>
void hammersley(tkernel<T> &);

template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void hammersley(tkernel<V<T, P>> &);




template <typename T>
void halton(tkernel<T> &, const unsigned int, const unsigned int);


template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void halton(tkernel<V<T, P>> &, const unsigned int, const unsigned int);




template <typename T>
void hammersley_sphere(tkernel<T> &, const HemisphereMapping = HemisphereMapping::Uniform);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void hammersley_sphere(tkernel<V<T, P>> &, const HemisphereMapping = HemisphereMapping::Uniform);





template <typename T>
void halton_sphere(tkernel<T> &, const unsigned int, const unsigned int, const HemisphereMapping = HemisphereMapping::Uniform);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void halton_sphere(tkernel<V<T, P>> &, const unsigned int, const unsigned int, const HemisphereMapping = HemisphereMapping::Uniform);




template <typename T>
void best_candidate(tkernel<T> &, unsigned int = 32);

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void best_candidate(tkernel<V<T, P>> &, unsigned int = 32);




template <typename T>
void n_rooks(tkernel<T> &);

template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void n_rooks(tkernel<V<T, P>> &);




template <typename T>
void multi_jittered(tkernel<T> &, const bool = false);

template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void multi_jittered(tkernel<V<T, P>> &, const bool = false);




template <typename T>
void golden_point_set(tkernel<T> &);

template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void golden_point_set(tkernel<V<T, P>> &);




} // namespace sample


} // namespace glkernel


#include "sample_generalized.hpp"
