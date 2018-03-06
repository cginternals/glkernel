#pragma once

#include "sample_generalized.h"
#include "AssertionMacros.h"
#include <iostream>




namespace glkernel
{


namespace sample
{




template <typename T>
void poisson_square(tkernel<T> &, const unsigned int)
{
    FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC2(T);
}

template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void poisson_square(tkernel<V<T, P>> &, const unsigned int)
{
    ASSERT_KERNEL_CELLTYPE_VEC2(V);
}


template <typename T1, typename T2>
void poisson_square(tkernel<T1> &, const T2, const unsigned int)
{
    FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC2(T1);
}

template <typename T1, typename T2,
          glm::precision P, template<typename, glm::precision> class V>
void poisson_square(tkernel<V<T1, P>> &, const T2, const unsigned int)
{
    ASSERT_KERNEL_CELLTYPE_VEC2(V);
    ASSERT_COMPONENTTYPE_EQUALITY(T1, T2);
}


template <typename T1, typename T2,
          glm::precision P, template<typename, glm::precision> class V>
void poisson_square(tkernel<T1> &, const V<T2, P> &, const unsigned int)
{
    FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC2(T1);
    FAIL_ON_PARAM_ASSUMING_COMPONENTTYPE(T1, V);
    //FAIL_ON_PARAM_ASSUMING_COMPONENTTYPE(T1, V)
}

template <typename T1, typename T2,
          glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
void poisson_square(tkernel<V1<T1, P>> &, const V2<T2, P> &, const unsigned int)
{
    FAIL_ON_PARAM_ASSUMING_COMPONENTTYPE(T1, V2);
    //FAIL_ON_PARAM_ASSUMING_COMPONENTTYPE(T1, V2)
}




template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void stratified(tkernel<V<T, P>> &)
{
    ASSERT_KERNEL_CELLTYPE_NOT_VEC4(V);
}




template <typename T>
void hammersley(tkernel<T> &)
{
    FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC2(T);
}

template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void hammersley(tkernel<V<T, P>> &)
{
    ASSERT_KERNEL_CELLTYPE_VEC2(V);
}




template <typename T>
void halton(tkernel<T> &, const unsigned int, const unsigned int)
{
    FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC2(T);
}


template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void halton(tkernel<V<T, P>> &, const unsigned int, const unsigned int)
{
    ASSERT_KERNEL_CELLTYPE_VEC2(V);
}




template <typename T>
void hammersley_sphere(tkernel<T> &, const HemisphereMapping)
{
    FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC3(T);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void hammersley_sphere(tkernel<V<T, P>> &, const HemisphereMapping)
{
    ASSERT_KERNEL_CELLTYPE_VEC3(V);
}





template <typename T>
void halton_sphere(tkernel<T> &, const unsigned int, const unsigned int, const HemisphereMapping)
{
    FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC3(T);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void halton_sphere(tkernel<V<T, P>> &, const unsigned int, const unsigned int, const HemisphereMapping)
{
    ASSERT_KERNEL_CELLTYPE_VEC3(V);
}




template <typename T>
void best_candidate(tkernel<T> &, unsigned int)
{
    FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC2_OR_VEC3(T);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void best_candidate(tkernel<V<T, P>> &, unsigned int)
{
    ASSERT_KERNEL_CELLTYPE_NOT_VEC4(V);
}




template <typename T>
void n_rooks(tkernel<T> &)
{
    FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC2(T);
}

template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void n_rooks(tkernel<V<T, P>> &)
{
    ASSERT_KERNEL_CELLTYPE_VEC2(V);
}




template <typename T>
void multi_jittered(tkernel<T> &, const bool)
{
    FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC2(T);
}

template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void multi_jittered(tkernel<V<T, P>> &, const bool)
{
    ASSERT_KERNEL_CELLTYPE_VEC2(V);
}




template <typename T>
void golden_point_set(tkernel<T> &)
{
    FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC2(T);
}

template <typename T,
          glm::precision P, template<typename, glm::precision> class V>
void golden_point_set(tkernel<V<T, P>> &)
{
    ASSERT_KERNEL_CELLTYPE_VEC2(V);
}




} // namespace sample


} // namespace glkernel
