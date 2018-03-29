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




} // namespace sort


} // namespace glkernel
