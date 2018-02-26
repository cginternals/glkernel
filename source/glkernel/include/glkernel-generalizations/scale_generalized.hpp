#pragma once

#include "scale_generalized.h"
#include "AssertionMacros.h"
#include <iostream>



namespace glkernel
{


namespace scale
{




template<typename T1, typename T2, typename T3, typename T4, typename T5>
void range(tkernel<T1> &, T2, T3, T4, T5)
{
    ASSERT_COMPONENTTYPE_EQUALITY(T1, T2, T3, T4, T5);
}


template <typename T1, typename T2, typename T3, typename T4, typename T5,
          glm::precision P, template<typename, glm::precision> class V>
void range(tkernel<T1> &, const V<T2, P> &, T3, T4, T5)
{
    FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_COMPONENTTYPE(T1);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
          glm::precision P, template<typename, glm::precision> class V>
void range(tkernel<T1> &, T2, const V<T3, P> &, T4, T5)
{
    FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_COMPONENTTYPE(T1);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
          glm::precision P, template<typename, glm::precision> class V>
void range(tkernel<T1> &, T2, T3, const V<T4, P> &, T5)
{
    FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_COMPONENTTYPE(T1);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
          glm::precision P, template<typename, glm::precision> class V>
void range(tkernel<T1> &, T2, T3, T4, const V<T5, P> &)
{
    FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_COMPONENTTYPE(T1);
}


template <typename T1, typename T2, typename T3, typename T4, typename T5,
          glm::precision P, template<typename, glm::precision> class V>
void range(tkernel<V<T1, P>> &, T2, T3, T4, T5)
{
    ASSERT_COMPONENTTYPE_EQUALITY(T1, T2, T3, T4, T5);
}


template <typename T1, typename T2, typename T3, typename T4, typename T5, glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
void range(tkernel<V1<T1, P>> &, const V2<T2, P> &, T3, T4, T5)
{
    FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_COMPONENTTYPE_OR_CELLTYPE(T1, V1);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
void range(tkernel<V1<T1, P>> &, T2, const V2<T3, P> &, T4, T5)
{
    FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_COMPONENTTYPE_OR_CELLTYPE(T1, V1);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
void range(tkernel<V1<T1, P>> &, T2, T3, const V2<T4, P> &, T5)
{
    FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_COMPONENTTYPE_OR_CELLTYPE(T1, V1);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
void range(tkernel<V1<T1, P>> &, T2, T3, T4, const V2<T5, P> &)
{
    FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_COMPONENTTYPE_OR_CELLTYPE(T1, V1);
}




} // namespace scale


} // namespace glkernel
