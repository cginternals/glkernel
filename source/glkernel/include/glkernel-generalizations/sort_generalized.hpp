#pragma once

#include "sort_generalized.h"
#include "AssertionMacros.h"
#include <iostream>


namespace glkernel
{


namespace sort
{




template <typename T1, typename T2>
void distance(tkernel<T1> &, const T2 &)
{
    ASSERT_TYPE_EQUALITY(T1, T2);
}




//template <typename T1, typename T2>
//void distance(tkernel<T1> &, const T2)
//{
//    ASSERT_COMPONENTTYPE_EQUALITY(T1, T2);
//}


//template<typename T1, typename T2, glm::precision P,
//         template<typename, glm::precision> class V>
//void distance(tkernel<T1> &, const V<T2, P> &)
//{
//    FAIL_ON_PARAM_ASSUMING_COMPONENTTYPE(T1, V);
//}




//template<typename T1, typename T2, glm::precision P,
//         template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
//void distance(tkernel<V1<T1, P>> &, const V2<T2, P> &)
//{
//    ASSERT_CELLTYPE_EQUALITY(V1, V2);
//    ASSERT_COMPONENTTYPE_EQUALITY(T1, T2);
//}


//template<typename T1, typename T2, glm::precision P,
//         template<typename, glm::precision> class V>
//void distance(tkernel<V<T1, P>> &, const T2)
//{
//    FAIL_ON_PARAM_ASSUMING_CELLTYPE(V, T2)
//}




} // namespace sort


} // namespace glkernel
