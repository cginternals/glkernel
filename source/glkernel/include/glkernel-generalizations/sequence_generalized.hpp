#pragma once

#include "sequence_generalized.h"
#include "AssertionMacros.h"
#include <iostream>


namespace glkernel
{


namespace sequence
{




template<typename T1, typename T2, typename T3>
void uniform(tkernel<T1> &, const T2, const T3)
{
    ASSERT_COMPONENTTYPE_EQUALITY(T1, T2, T3);
}


template<typename T1, typename T2, typename T3,
         glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<T1> &, const V<T2, P> &, const T3)
{
    FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_SCALAR(T1);
}

template<typename T1, typename T2, typename T3,
         glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<T1> &, const T2, const V<T3, P> &)
{
    FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_SCALAR(T1);
}


template <typename T1, typename T2, typename T3,
          glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<V<T1, P>> &, const T2, const T3)
{
    ASSERT_COMPONENTTYPE_EQUALITY(T1, T2, T3);
}


template <typename T1, typename T2, typename T3,
          glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
void uniform(tkernel<V1<T1, P>> &, const V2<T2, P> &, const T3)
{
    FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_SCALAR_OR_VECTORIAL(T1, V1);
}

template <typename T1, typename T2, typename T3,
          glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2>
void uniform(tkernel<V1<T1, P>> &, const T2, const V2<T3, P> &)
{
    FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_SCALAR_OR_VECTORIAL(T1, V1);
}


template <typename T1, typename T2, typename T3,
          glm::precision P,
          template<typename, glm::precision> class V1, template<typename, glm::precision> class V2, template<typename, glm::precision> class V3>
void uniform(tkernel<V1<T1, P>> &, const V2<T2, P> &, const V3<T3, P> &)
{
    ASSERT_COMPONENTTYPE_EQUALITY(T1, T2, T3);
    ASSERT_CELLTYPE_EQUALITY(V1, V2, V3);
}




} // namespace sequence


} // namespace glkernel
