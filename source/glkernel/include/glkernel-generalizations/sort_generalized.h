#pragma once

#include <glkernel/Kernel.h>

#include <glm/gtc/type_precision.hpp>


namespace glkernel
{


namespace sort
{




template <typename T1, typename T2>
void distance(tkernel<T1> &, const T2 &);




//template <typename T1, typename T2>
//void distance(tkernel<T1> &, const T2);


//template<typename T1, typename T2, glm::precision P,
//         template<typename, glm::precision> class V>
//void distance(tkernel<T1> &, const V<T2, P> &);




//template<typename T1, typename T2, glm::precision P,
//         template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
//void distance(tkernel<V1<T1, P>> &, const V2<T2, P> &);


//template<typename T1, typename T2, glm::precision P,
//         template<typename, glm::precision> class V>
//void distance(tkernel<V<T1, P>> &, const T2);




} // namespace sort


} // namespace glkernel


#include "sort_generalized.hpp"
