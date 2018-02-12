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


template <typename T, glm::precision P, template<typename, glm::precision> class V>
void gradient(tkernel<V<T, P>> &
    , const GradientNoiseType
    , const OctaveType
    , const unsigned int
    , const unsigned int)
{
    FAIL_KERNEL_CELLTYPE_SCALAR(V);
}


} // namespace noise




namespace sample
{


template <typename T>
void poisson_square(tkernel<T> &, const unsigned int)
{
    FAIL_KERNEL_CELLTYPE_VEC2(T);
}

template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void poisson_square(tkernel<V<T, P>> &, const unsigned int)
{
    CHECK_KERNEL_CELLTYPE_VEC2(V);
}


template <typename T1, typename T2>
void poisson_square(tkernel<T1> &, const T2, const unsigned int)
{
    FAIL_KERNEL_CELLTYPE_VEC2(T1);
    CHECK_TYPE_EQUALITY(T1, T2);
}

template <typename T1, typename T2,
          glm::precision P, template<typename, glm::precision> class V>
void poisson_square(tkernel<V<T1, P>> &, const T2, const unsigned int)
{
    CHECK_KERNEL_CELLTYPE_VEC2(V);
    CHECK_TYPE_EQUALITY(T1, T2);
}


template <typename T1, typename T2,
          glm::precision P, template<typename, glm::precision> class V>
void poisson_square(tkernel<T1> &, const V<T2, P> &, const unsigned int)
{
    FAIL_KERNEL_CELLTYPE_VEC2(T1);
    FAIL_PARAM_TYPE_T(T1, V);
    CHECK_TYPE_EQUALITY(T1, T2);
}

template <typename T1, typename T2,
          glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
void poisson_square(tkernel<V1<T1, P>> &, const V2<T2, P> &, const unsigned int)
{
    CHECK_KERNEL_CELLTYPE_VEC2(V1);
    FAIL_PARAM_TYPE_T(T1, V2);
    CHECK_TYPE_EQUALITY(T1, T2);
}


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
