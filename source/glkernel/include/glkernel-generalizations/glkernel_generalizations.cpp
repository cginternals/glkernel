#pragma once

#include "glkernel_generalizations.h"
#include "AssertionMacros.h"
#include <iostream>


namespace glkernel
{




namespace noise
{


template<typename T1, typename T2, typename T3>
void uniform(tkernel<T1> &, const T2, const T3)
{
    CHECK_TYPE_FLOATING(T1);
    CHECK_TYPE_EQUALITY(T1, T2, T3);
}

template <typename T1, typename T2, typename T3,
          glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<V<T1, P>> &, const T2, const T3)
{
    CHECK_TYPE_FLOATING(T1);
    CHECK_TYPE_EQUALITY(T1, T2, T3);
}

template <typename T1, typename T2, typename T3,
          glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2, template<typename, glm::precision> class V3>
void uniform(tkernel<V1<T1, P>> &, const V2<T2, P> &, const V3<T3, P> &)
{
    CHECK_TYPE_FLOATING(T1);
    CHECK_TYPE_EQUALITY(T1, T2, T3);
    CHECK_CELLTYPE_EQUALITY(V1, V2, V3);
}


template<typename T1, typename T2, typename T3>
void normal(tkernel<T1> &, const T2, const T3)
{
    CHECK_TYPE_FLOATING(T1);
    CHECK_TYPE_EQUALITY(T1, T2, T3);
}

template <typename T1, typename T2, typename T3,
          glm::precision P, template<typename, glm::precision> class V>
void normal(tkernel<V<T1, P>> &, const T2, const T3)
{
    CHECK_TYPE_FLOATING(T1);
    CHECK_TYPE_EQUALITY(T1, T2, T3);
}

template <typename T1, typename T2, typename T3,
          glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2, template<typename, glm::precision> class V3>
void normal(tkernel<V1<T1, P>> &, const V2<T2, P> &, const V3<T3, P> &)
{
    CHECK_TYPE_FLOATING(T1);
    CHECK_TYPE_EQUALITY(T1, T2, T3);
    CHECK_CELLTYPE_EQUALITY(V1, V2, V3);
}


} // namespace noise




namespace sample
{



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
