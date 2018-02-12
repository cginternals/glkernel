#pragma once

#include "TypeTraits.cpp"
#include "ConstExpressions.cpp"
#include "StringMacros.h"


//#define CHECK_FLOATING_TYPE(T) static_assert(std::is_floating_point<T>::value, KERNEL_FLOATING)
//#define CHECK_TYPE_EQUALITY(T1, T2, T3) static_assert(areSameType<T1, T2, T3>(), PARAM_MATCH_KERNEL)
//#define CHECK_CELLTYPE_EQUALITY(V1, V2, V3) static_assert(areSameCelltype<V1, V2, V3>(), PARAM_MATCH_CELL)




#define CHECK_TYPE_FLOATING(T) static_assert(std::is_floating_point<T>::value, KERNEL_FLOATING)



// Checks, if kernel is of CELLtype vec2.
#define CHECK_KERNEL_CELLTYPE_VEC2(V)                                                                     \
    static_assert( (areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, glm::tvec2>()) ||       \
                   (!areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, glm::tvec2>()) ||      \
                   !(areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, glm::tvec2>()) ||     \
                   (!areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, glm::tvec2>())        \
                   , VEC2_KERNEL_CELLTYPE_MATCH_VEC3);                                                      \
    static_assert( (areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, glm::tvec2>()) ||       \
                   (!areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, glm::tvec2>()) ||      \
                   !(areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, glm::tvec2>()) ||     \
                   (!areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, glm::tvec2>())        \
                   , VEC2_KERNEL_CELLTYPE_MATCH_VEC4);

// Checks, if kernel is of CELLtype vec3.
#define CHECK_KERNEL_CELLTYPE_VEC3(V)                                                                     \
    static_assert( (areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, glm::tvec3>()) ||       \
                   (!areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, glm::tvec3>()) ||      \
                   !(areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, glm::tvec3>()) ||     \
                   (!areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, glm::tvec3>())        \
                   , VEC3_KERNEL_CELLTYPE_MATCH_VEC2);                                                      \
    static_assert( (areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, glm::tvec3>()) ||       \
                   (!areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, glm::tvec3>()) ||      \
                   !(areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, glm::tvec3>()) ||     \
                   (!areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, glm::tvec3>())        \
                   , VEC3_KERNEL_CELLTYPE_MATCH_VEC4);

// Checks, if kernel is of CELLtype vec4.
#define CHECK_KERNEL_CELLTYPE_VEC4(V)                                                                     \
    static_assert( (areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, glm::tvec4>()) ||       \
                   (!areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, glm::tvec4>()) ||      \
                   !(areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, glm::tvec4>()) ||     \
                   (!areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, glm::tvec4>())        \
                   , VEC4_KERNEL_CELLTYPE_MATCH_VEC2);                                                      \
    static_assert( (areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, glm::tvec4>()) ||       \
                   (!areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, glm::tvec4>()) ||      \
                   !(areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, glm::tvec4>()) ||     \
                   (!areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, glm::tvec4>())        \
                   , VEC4_KERNEL_CELLTYPE_MATCH_VEC3);


// Fail, because vec2 kernel is of some scalar type
#define FAIL_KERNEL_CELLTYPE_VEC2(T)                                             \
    static_assert(!areSameType<T, float>(), VEC2_KERNEL_CELLTYPE_MATCH_FLOAT);   \
    static_assert(!areSameType<T, double>(), VEC2_KERNEL_CELLTYPE_MATCH_DOUBLE);
// Fail, because vec3 kernel is of some scalar type
#define FAIL_KERNEL_CELLTYPE_VEC3(T)                                             \
    static_assert(!areSameType<T, float>(), VEC3_KERNEL_CELLTYPE_MATCH_FLOAT);   \
    static_assert(!areSameType<T, double>(), VEC3_KERNEL_CELLTYPE_MATCH_DOUBLE);
// Fail, because vec4 kernel is of some scalar type
#define FAIL_KERNEL_CELLTYPE_VEC4(T)                                             \
    static_assert(!areSameType<T, float>(), VEC4_KERNEL_CELLTYPE_MATCH_FLOAT);   \
    static_assert(!areSameType<T, double>(), VEC4_KERNEL_CELLTYPE_MATCH_DOUBLE);

// Fail, because scalar kernel is of some vectorial type
#define FAIL_KERNEL_CELLTYPE_SCALAR(V)                                                  \
    static_assert(!areSameCelltype<V, glm::tvec2>(), SCALAR_KERNEL_CELLTYPE_MATCH_VEC2); \
    static_assert(!areSameCelltype<V, glm::tvec3>(), SCALAR_KERNEL_CELLTYPE_MATCH_VEC3); \
    static_assert(!areSameCelltype<V, glm::tvec4>(), SCALAR_KERNEL_CELLTYPE_MATCH_VEC4);


// Fail, because scalar parameter (float or double) is of some vectorial celltype
#define FAIL_PARAM_TYPE_T(T, V) \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec2>()), FLOAT_PARAM_TYPE_MATCH_VEC2); \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec3>()), FLOAT_PARAM_TYPE_MATCH_VEC3); \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec4>()), FLOAT_PARAM_TYPE_MATCH_VEC4); \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec2>()), DOUBLE_PARAM_TYPE_MATCH_VEC2); \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec3>()), DOUBLE_PARAM_TYPE_MATCH_VEC3); \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec4>()), DOUBLE_PARAM_TYPE_MATCH_VEC4);



// Checks if all arguments are of the same type.
// Implicitly assumes that arguements are parameters of a method including kernel as first argument!
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

// Checks if all arguments are of the same CELLtype.
// Implicitly assumes that arguements are parameters of a method including kernel as first argument!
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

