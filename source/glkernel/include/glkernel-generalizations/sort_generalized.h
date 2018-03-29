#pragma once

#include <glkernel/Kernel.h>

#include <glm/gtc/type_precision.hpp>


/*
*  This file contains further overloaded methods of the namespace glkernel::sort
*  that exist in parallel to the ones in sort.h.
*  These methods feature generalized signatures that are intented to match all the
*  prohibited calls. This way, calling a method with wrong arguments does not result
*  in a template deduction failure, but instead gives specific and verbose error messages.
*/


namespace glkernel
{


namespace sort
{




template <typename T1, typename T2>
void distance(tkernel<T1> &, const T2 &);




} // namespace sort


} // namespace glkernel


#include "sort_generalized.hpp"
