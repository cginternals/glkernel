#pragma once

#include <glkernel/Kernel.h>

#include <glm/gtc/type_precision.hpp>


/*
*  This file contains further overloaded methods of the namespace glkernel::scale
*  that exist in parallel to the ones in scale.h.
*  These methods feature generalized signatures that are intented to match all the
*  prohibited calls. This way, calling a method with wrong arguments does not result
*  in a template deduction failure, but instead gives specific and verbose error messages.
*/


namespace glkernel
{


namespace scale
{




template<typename T1, typename T2, typename T3, typename T4, typename T5>
void range(tkernel<T1> &, T2, T3, T4 = 0, T5 = 1);


template <typename T1, typename T2, typename T3, typename T4, typename T5,
          glm::precision P, template<typename, glm::precision> class V>
void range(tkernel<T1> &, const V<T2, P> &, T3, T4 = 0, T5 = 1);

template <typename T1, typename T2, typename T3, typename T4, typename T5,
          glm::precision P, template<typename, glm::precision> class V>
void range(tkernel<T1> &, T2, const V<T3, P> &, T4 = 0, T5 = 1);

template <typename T1, typename T2, typename T3, typename T4, typename T5,
          glm::precision P, template<typename, glm::precision> class V>
void range(tkernel<T1> &, T2, T3, const V<T4, P> & = 0, T5 = 1);

template <typename T1, typename T2, typename T3, typename T4, typename T5,
          glm::precision P, template<typename, glm::precision> class V>
void range(tkernel<T1> &, T2, T3, T4 = 0, const V<T5, P> & = 1);


template <typename T1, typename T2, typename T3, typename T4, typename T5,
          glm::precision P, template<typename, glm::precision> class V>
void range(tkernel<V<T1, P>> &, T2, T3, T4 = 0, T5 = 1);


template <typename T1, typename T2, typename T3, typename T4, typename T5, glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
void range(tkernel<V1<T1, P>> &, const V2<T2, P> &, T3, T4 = 0, T5 = 1);

template <typename T1, typename T2, typename T3, typename T4, typename T5, glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
void range(tkernel<V1<T1, P>> &, T2, const V2<T3, P> &, T4 = 0, T5 = 1);

template <typename T1, typename T2, typename T3, typename T4, typename T5, glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
void range(tkernel<V1<T1, P>> &, T2, T3, const V2<T4, P> & = 0, T5 = 1);

template <typename T1, typename T2, typename T3, typename T4, typename T5, glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
void range(tkernel<V1<T1, P>> &, T2, T3, T4 = 0, const V2<T5, P> & = 1);




} // namespace scale


} // namespace glkernel


#include "scale_generalized.hpp"
