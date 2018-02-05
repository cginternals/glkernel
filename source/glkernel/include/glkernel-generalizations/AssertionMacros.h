#pragma once

#include "TypeTraits.cpp"
#include "ConstExpressions.cpp"
#include "StringMacros.h"


//#define CHECK_FLOATING_TYPE(T) static_assert(std::is_floating_point<T>::value, KERNEL_FLOATING)
//#define CHECK_TYPE_EQUALITY(T1, T2, T3) static_assert(areSameType<T1, T2, T3>(), PARAM_MATCH_KERNEL)
//#define CHECK_CELLTYPE_EQUALITY(V1, V2, V3) static_assert(areSameCelltype<V1, V2, V3>(), PARAM_MATCH_CELL)




#define CHECK_TYPE_FLOATING(T) static_assert(std::is_floating_point<T>::value, KERNEL_FLOATING)


#define CHECK_TYPE_EQUALITY(T, ...)                                                 \
    static_assert( (areSameType<T, float>() && areSameType<T, __VA_ARGS__>()) ||    \
                   (!areSameType<T, float>() && areSameType<T, __VA_ARGS__>()) ||   \
                   !(areSameType<T, float>() && !areSameType<T, __VA_ARGS__>()) ||  \
                   (!areSameType<T, float>() && !areSameType<T, __VA_ARGS__>())     \
                   , PARAM_MATCH_FLOAT);                                            \
    static_assert( (areSameType<T, double>() && areSameType<T, __VA_ARGS__>()) ||   \
                   (!areSameType<T, double>() && areSameType<T, __VA_ARGS__>()) ||  \
                   !(areSameType<T, double>() && !areSameType<T, __VA_ARGS__>()) || \
                   (!areSameType<T, double>() && !areSameType<T, __VA_ARGS__>())    \
                   , PARAM_MATCH_DOUBLE);


#define CHECK_CELLTYPE_EQUALITY(V, ...)                                                             \
    static_assert( (areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, __VA_ARGS__>()) ||       \
                   (!areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, __VA_ARGS__>()) ||      \
                   !(areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, __VA_ARGS__>()) ||     \
                   (!areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, __VA_ARGS__>())        \
                   , PARAM_MATCH_VEC2);                                                             \
    static_assert( (areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, __VA_ARGS__>()) ||       \
                   (!areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, __VA_ARGS__>()) ||      \
                   !(areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, __VA_ARGS__>()) ||     \
                   (!areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, __VA_ARGS__>())        \
                   , PARAM_MATCH_VEC3);                                                             \
    static_assert( (areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, __VA_ARGS__>()) ||       \
                   (!areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, __VA_ARGS__>()) ||      \
                   !(areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, __VA_ARGS__>()) ||     \
                   (!areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, __VA_ARGS__>())        \
                   , PARAM_MATCH_VEC4);


//#define CHECK_FLOATING_TYPE(T) static_assert(std::is_floating_point<T>::value, KERNEL_FLOATING)
//#define CHECK_TYPE_EQUALITY(...) checkTypeEquality<__VA_ARGS__>()

