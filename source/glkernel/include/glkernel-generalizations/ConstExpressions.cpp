#pragma once

#include <typeinfo>

#include <glkernel/Kernel.h>

#include "TypeTraits.cpp"
#include "StringMacros.h"


namespace glkernel
{

namespace noise
{


/*
 * These methods are mainly used for actually typing the assertions.
 * Later the lines are copied to AssertionMacros.h.
 */


template<typename T, typename... Ts>
constexpr void checkTypeEquality()
{
    static_assert( (areSameType<T, float>() && areSameType<T, Ts...>()) ||
                   (!areSameType<T, float>() && areSameType<T, Ts...>()) ||
                   !(areSameType<T, float>() && !areSameType<T, Ts...>()) ||
                   (!areSameType<T, float>() && !areSameType<T, Ts...>())
                   , PARAM_MATCH_FLOAT);

    static_assert( (areSameType<T, double>() && areSameType<T, Ts...>()) ||
                   (!areSameType<T, double>() && areSameType<T, Ts...>()) ||
                   !(areSameType<T, double>() && !areSameType<T, Ts...>()) ||
                   (!areSameType<T, double>() && !areSameType<T, Ts...>())
                   , PARAM_MATCH_DOUBLE);
}

template<template<typename, glm::precision> class V, template<typename, glm::precision> class... Vs>
constexpr void checkCelltypeEquality()
{
    static_assert( (areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, Vs...>())   ||
                   (!areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, Vs...>())  ||
                   !(areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, Vs...>()) ||
                   (!areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, Vs...>())
                   , PARAM_MATCH_VEC2);

    static_assert( (areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, Vs...>())   ||
                   (!areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, Vs...>())  ||
                   !(areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, Vs...>()) ||
                   (!areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, Vs...>())
                   , PARAM_MATCH_VEC3);

    static_assert( (areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, Vs...>())   ||
                   (!areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, Vs...>())  ||
                   !(areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, Vs...>()) ||
                   (!areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, Vs...>())
                   , PARAM_MATCH_VEC4);
}



} // testEnv

} // glkernel
