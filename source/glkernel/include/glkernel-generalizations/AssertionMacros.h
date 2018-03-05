#pragma once

#include "TypeTraits.cpp"
#include "StringMacros.h"




// Asserts, that kernel is of cell type vec2.
#define ASSERT_KERNEL_CELLTYPE_VEC2(V)                                                              \
    static_assert( (areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, glm::tvec2>()) ||        \
                   (!areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, glm::tvec2>()) ||       \
                   !(areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, glm::tvec2>()) ||      \
                   (!areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, glm::tvec2>())         \
                   , VEC2_KERNEL_CELLTYPE_MATCH_VEC3);                                              \
    static_assert( (areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, glm::tvec2>()) ||        \
                   (!areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, glm::tvec2>()) ||       \
                   !(areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, glm::tvec2>()) ||      \
                   (!areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, glm::tvec2>())         \
                   , VEC2_KERNEL_CELLTYPE_MATCH_VEC4);

// Asserts, that kernel is of cell type vec3.
#define ASSERT_KERNEL_CELLTYPE_VEC3(V)                                                              \
    static_assert( (areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, glm::tvec3>()) ||        \
                   (!areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, glm::tvec3>()) ||       \
                   !(areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, glm::tvec3>()) ||      \
                   (!areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, glm::tvec3>())         \
                   , VEC3_KERNEL_CELLTYPE_MATCH_VEC2);                                              \
    static_assert( (areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, glm::tvec3>()) ||        \
                   (!areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, glm::tvec3>()) ||       \
                   !(areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, glm::tvec3>()) ||      \
                   (!areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, glm::tvec3>())         \
                   , VEC3_KERNEL_CELLTYPE_MATCH_VEC4);

// Asserts, that kernel is of cell type vec4.
#define ASSERT_KERNEL_CELLTYPE_VEC4(V)                                                              \
    static_assert( (areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, glm::tvec4>()) ||        \
                   (!areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, glm::tvec4>()) ||       \
                   !(areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, glm::tvec4>()) ||      \
                   (!areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, glm::tvec4>())         \
                   , VEC4_KERNEL_CELLTYPE_MATCH_VEC2);                                              \
    static_assert( (areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, glm::tvec4>()) ||        \
                   (!areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, glm::tvec4>()) ||       \
                   !(areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, glm::tvec4>()) ||      \
                   (!areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, glm::tvec4>())         \
                   , VEC4_KERNEL_CELLTYPE_MATCH_VEC3);

#define ASSERT_KERNEL_CELLTYPE_NOT_VEC2(V)                                          \
    static_assert(!areSameCelltype<V, glm::tvec2>(), NOT_VEC2_KERNEL_CELLTYPE);

#define ASSERT_KERNEL_CELLTYPE_NOT_VEC3(V)                                          \
    static_assert(!areSameCelltype<V, glm::tvec3>(), NOT_VEC3_KERNEL_CELLTYPE);

#define ASSERT_KERNEL_CELLTYPE_NOT_VEC4(V)                                          \
    static_assert(!areSameCelltype<V, glm::tvec4>(), NOT_VEC4_KERNEL_CELLTYPE);



// Fail, because (scalar) kernel is of some vectorial type.
#define FAIL_ON_VECTORIAL_KERNEL_CELLTYPE_ASSUMING_SCALAR(V)                                        \
    static_assert(!areSameCelltype<V, glm::tvec2>(), SCALAR_KERNEL_CELLTYPE_MATCH_VEC2);            \
    static_assert(!areSameCelltype<V, glm::tvec3>(), SCALAR_KERNEL_CELLTYPE_MATCH_VEC3);            \
    static_assert(!areSameCelltype<V, glm::tvec4>(), SCALAR_KERNEL_CELLTYPE_MATCH_VEC4);

// Fail, because (vec2) kernel is of some scalar type.
#define FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC2(T)                                             \
    static_assert(!areSameType<T, float>(), VEC2_KERNEL_CELLTYPE_MATCH_FLOAT);                      \
    static_assert(!areSameType<T, double>(), VEC2_KERNEL_CELLTYPE_MATCH_DOUBLE);

// Fail, because (vec3) kernel is of some scalar type.
#define FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC3(T)                                             \
    static_assert(!areSameType<T, float>(), VEC3_KERNEL_CELLTYPE_MATCH_FLOAT);                      \
    static_assert(!areSameType<T, double>(), VEC3_KERNEL_CELLTYPE_MATCH_DOUBLE);

// Fail, because (vec4) kernel is of some scalar type.
#define FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC4(T)                                             \
    static_assert(!areSameType<T, float>(), VEC4_KERNEL_CELLTYPE_MATCH_FLOAT);                      \
    static_assert(!areSameType<T, double>(), VEC4_KERNEL_CELLTYPE_MATCH_DOUBLE);


#define FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC2_OR_VEC3(T)                                     \
    static_assert(!areSameType<T, float>(), VEC2_OR_VEC3_KERNEL_CELLTYPE_MATCH_FLOAT);              \
    static_assert(!areSameType<T, double>(), VEC2_OR_VEC3_KERNEL_CELLTYPE_MATCH_DOUBLE);




#define ASSERT_TYPE_EQUALITY(...)                                       \
    static_assert(areSameType<__VA_ARGS__>(), ARGUMENTS_MUST_EQUAL)


// Checks if all arguments are of the same component type.
// Implicitly assumes that arguements are parameters of a method including kernel as first argument!
#define ASSERT_COMPONENTTYPE_EQUALITY(T, ...)                                                       \
    static_assert( (areSameType<T, float>() && areSameType<T, __VA_ARGS__>()) ||                    \
                   (!areSameType<T, float>() && areSameType<T, __VA_ARGS__>()) ||                   \
                   !(areSameType<T, float>() && !areSameType<T, __VA_ARGS__>()) ||                  \
                   (!areSameType<T, float>() && !areSameType<T, __VA_ARGS__>())                     \
                   , PARAMS_MATCH_FLOAT);                                                           \
    static_assert( (areSameType<T, double>() && areSameType<T, __VA_ARGS__>()) ||                   \
                   (!areSameType<T, double>() && areSameType<T, __VA_ARGS__>()) ||                  \
                   !(areSameType<T, double>() && !areSameType<T, __VA_ARGS__>()) ||                 \
                   (!areSameType<T, double>() && !areSameType<T, __VA_ARGS__>())                    \
                   , PARAMS_MATCH_DOUBLE);

// Checks if all arguments are of the same cell type.
// Implicitly assumes that arguements are parameters of a method including kernel as first argument!
#define ASSERT_CELLTYPE_EQUALITY(V, ...)                                                            \
    static_assert( (areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, __VA_ARGS__>()) ||       \
                   (!areSameCelltype<V, glm::tvec2>() && areSameCelltype<V, __VA_ARGS__>()) ||      \
                   !(areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, __VA_ARGS__>()) ||     \
                   (!areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, __VA_ARGS__>())        \
                   , PARAMS_MATCH_VEC2);                                                            \
    static_assert( (areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, __VA_ARGS__>()) ||       \
                   (!areSameCelltype<V, glm::tvec3>() && areSameCelltype<V, __VA_ARGS__>()) ||      \
                   !(areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, __VA_ARGS__>()) ||     \
                   (!areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, __VA_ARGS__>())        \
                   , PARAMS_MATCH_VEC3);                                                            \
    static_assert( (areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, __VA_ARGS__>()) ||       \
                   (!areSameCelltype<V, glm::tvec4>() && areSameCelltype<V, __VA_ARGS__>()) ||      \
                   !(areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, __VA_ARGS__>()) ||     \
                   (!areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, __VA_ARGS__>())        \
                   , PARAMS_MATCH_VEC4);




// Fail, because scalar parameter (float or double) is of some vectorial celltype
#define FAIL_ON_PARAM_ASSUMING_COMPONENTTYPE(T, V)    \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec2>()), FLOAT_PARAM_MATCH_VEC2);    \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec3>()), FLOAT_PARAM_MATCH_VEC3);    \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec4>()), FLOAT_PARAM_MATCH_VEC4);    \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec2>()), DOUBLE_PARAM_MATCH_VEC2);  \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec3>()), DOUBLE_PARAM_MATCH_VEC3);  \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec4>()), DOUBLE_PARAM_MATCH_VEC4);


// Fail, because vectorial parameter is of some scalar celltype
#define FAIL_ON_PARAM_ASSUMING_CELLTYPE(V, T)    \
    static_assert( !(areSameCelltype<V, glm::tvec2>() && areSameType<T, float>()), VEC2_PARAM_MATCH_FLOAT);     \
    static_assert( !(areSameCelltype<V, glm::tvec2>() && areSameType<T, double>()), VEC2_PARAM_MATCH_DOUBLE);   \
    static_assert( !(areSameCelltype<V, glm::tvec3>() && areSameType<T, float>()), VEC3_PARAM_MATCH_FLOAT);     \
    static_assert( !(areSameCelltype<V, glm::tvec3>() && areSameType<T, double>()), VEC3_PARAM_MATCH_DOUBLE);   \
    static_assert( !(areSameCelltype<V, glm::tvec4>() && areSameType<T, float>()), VEC4_PARAM_MATCH_FLOAT);     \
    static_assert( !(areSameCelltype<V, glm::tvec4>() && areSameType<T, double>()), VEC4_PARAM_MATCH_DOUBLE);




#define FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_COMPONENTTYPE(T)               \
    static_assert( !areSameType<T, float>(),  PARAMS_EQUAL_MATCH_FLOAT);    \
    static_assert( !areSameType<T, double>(), PARAMS_EQUAL_MATCH_DOUBLE);


#define FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_COMPONENTTYPE_OR_CELLTYPE(T, V)                                                \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec2>()),  PARAMS_EQUAL_MATCH_FLOAT_OR_VEC2);      \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec3>()),  PARAMS_EQUAL_MATCH_FLOAT_OR_VEC3);      \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec4>()),  PARAMS_EQUAL_MATCH_FLOAT_OR_VEC4);      \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec2>()), PARAMS_EQUAL_MATCH_DOUBLE_OR_VEC2);     \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec3>()), PARAMS_EQUAL_MATCH_DOUBLE_OR_VEC3);     \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec4>()), PARAMS_EQUAL_MATCH_DOUBLE_OR_VEC4);





