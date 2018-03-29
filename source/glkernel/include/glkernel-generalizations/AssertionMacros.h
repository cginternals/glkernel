#pragma once

#include "TypeTraits.cpp"
#include "StringMacros.h"




/*
 * Asserts, that kernel is of cell type glm::vec2.
 */
#define ASSERT_KERNEL_CELLTYPE_VEC2(V)                                                                                          \
    static_assert(!(areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, glm::tvec2>()), VEC2_KERNEL_CELLTYPE_MATCH_VEC3);   \
    static_assert(!(areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, glm::tvec2>()), VEC2_KERNEL_CELLTYPE_MATCH_VEC4);

/*
 * Asserts, that kernel is of cell type glm::vec3.
 */
#define ASSERT_KERNEL_CELLTYPE_VEC3(V)                                                                                          \
    static_assert(!(areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, glm::tvec3>()), VEC3_KERNEL_CELLTYPE_MATCH_VEC2);   \
    static_assert(!(areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, glm::tvec3>()), VEC3_KERNEL_CELLTYPE_MATCH_VEC4);

/*
 * Asserts, that kernel is of cell type glm::vec4.
 */
#define ASSERT_KERNEL_CELLTYPE_VEC4(V)                                                                                          \
    static_assert( !(areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, glm::tvec4>()), VEC4_KERNEL_CELLTYPE_MATCH_VEC2);  \
    static_assert( !(areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, glm::tvec4>()), VEC4_KERNEL_CELLTYPE_MATCH_VEC3);


/*
 * Asserts, that kernel is of a cell type anything but glm::vec2.
 */
#define ASSERT_KERNEL_CELLTYPE_NOT_VEC2(V)                                      \
    static_assert(!areSameCelltype<V, glm::tvec2>(), NOT_VEC2_KERNEL_CELLTYPE);

/*
 * Asserts, that kernel is of a cell type anything but glm::vec3.
 */
#define ASSERT_KERNEL_CELLTYPE_NOT_VEC3(V)                                      \
    static_assert(!areSameCelltype<V, glm::tvec3>(), NOT_VEC3_KERNEL_CELLTYPE);

/*
 * Asserts, that kernel is of a cell type anything but glm::vec4.
 */
#define ASSERT_KERNEL_CELLTYPE_NOT_VEC4(V)                                      \
    static_assert(!areSameCelltype<V, glm::tvec4>(), NOT_VEC4_KERNEL_CELLTYPE);




/*
 * The intention of this macro is to lead to a guaranteed failure, since it is supposed to be used when the kernel is of
 * a vectorial (V: glm::vec2, glm::vec3, glm::vec4) cell type, although it should be a scalar one.
 */
#define FAIL_ON_VECTORIAL_KERNEL_CELLTYPE_ASSUMING_SCALAR(V)                                \
    static_assert(!areSameCelltype<V, glm::tvec2>(), SCALAR_KERNEL_CELLTYPE_MATCH_VEC2);    \
    static_assert(!areSameCelltype<V, glm::tvec3>(), SCALAR_KERNEL_CELLTYPE_MATCH_VEC3);    \
    static_assert(!areSameCelltype<V, glm::tvec4>(), SCALAR_KERNEL_CELLTYPE_MATCH_VEC4);

/*
 * The intention of this macro is to lead to a guaranteed failure, since it is supposed to be used when the kernel is of
 * a scalar cell type (T: float, double), although it should be of cell type glm::vec2.
 */
#define FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC2(T)                                     \
    static_assert(!areSameType<T, float>(), VEC2_KERNEL_CELLTYPE_MATCH_FLOAT);              \
    static_assert(!areSameType<T, double>(), VEC2_KERNEL_CELLTYPE_MATCH_DOUBLE);

/*
 * The intention of this macro is to lead to a guaranteed failure, since it is supposed to be used when the kernel is of
 * a scalar cell type (T: float, double), although it should be of cell type glm::vec3.
 */
#define FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC3(T)                                     \
    static_assert(!areSameType<T, float>(), VEC3_KERNEL_CELLTYPE_MATCH_FLOAT);              \
    static_assert(!areSameType<T, double>(), VEC3_KERNEL_CELLTYPE_MATCH_DOUBLE);

/*
 * The intention of this macro is to lead to a guaranteed failure, since it is supposed to be used when the kernel is of
 * a scalar cell type (T: float, double), although it should be of cell type glm::vec4.
 */
#define FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC4(T)                                     \
    static_assert(!areSameType<T, float>(), VEC4_KERNEL_CELLTYPE_MATCH_FLOAT);              \
    static_assert(!areSameType<T, double>(), VEC4_KERNEL_CELLTYPE_MATCH_DOUBLE);

/*
 * The intention of this macro is to lead to a guaranteed failure, since it is supposed to be used when the kernel is of
 * a scalar cell type (T: float, double), although it should be of cell type glm::vec4.
 */
#define FAIL_ON_SCALAR_KERNEL_CELLTYPE_ASSUMING_VEC2_OR_VEC3(T)                                                     \
    static_assert(!areSameType<T, float>(), VEC2_OR_VEC3_KERNEL_CELLTYPE_MATCH_FLOAT);                              \
    static_assert(!areSameType<T, double>(), VEC2_OR_VEC3_KERNEL_CELLTYPE_MATCH_DOUBLE);




/*
 * Asserts, that all arguments are of the same component type.
 * Implicitly assumes that arguements are type template parameters of a method
 * including the kernel's type template as first argument!
 */
#define ASSERT_COMPONENTTYPE_EQUALITY(T, ...)                                                                       \
    static_assert( !(areSameType<T, float>() && !areSameType<T, __VA_ARGS__>()), PARAMS_MATCH_FLOAT);               \
    static_assert( !(areSameType<T, double>() && !areSameType<T, __VA_ARGS__>()), PARAMS_MATCH_DOUBLE);

/*
 * Asserts, that all arguments are of the same cell type.
 * Implicitly assumes that arguements are template template parameters of a method
 * including the kernel's template template as first argument!
 */
#define ASSERT_CELLTYPE_EQUALITY(V, ...)                                                                            \
    static_assert( !(areSameCelltype<V, glm::tvec2>() && !areSameCelltype<V, __VA_ARGS__>()), PARAMS_MATCH_VEC2);   \
    static_assert( !(areSameCelltype<V, glm::tvec3>() && !areSameCelltype<V, __VA_ARGS__>()), PARAMS_MATCH_VEC3);   \
    static_assert( !(areSameCelltype<V, glm::tvec4>() && !areSameCelltype<V, __VA_ARGS__>()), PARAMS_MATCH_VEC4);

/*
 * Asserts, that all arguments are of the same type.
 * Implicitly assumes that arguements are type template parameters of a method
 * including the kernel's type template as first argument!
 *
 * This version differentiates from the two beforenamed,since it does not differentiate between
 * scalar cell types (specifically type template arguments) and vectorial cell types (specifically template template arguments).
 * Because of that, the triggered string literals are not able to hint to concrete cell types (float, double, glm::vec2, ...).
 * What seems to be worse (= less specific) than the other two options is the only way to go, if a method is templated by
 * type templates only (e.g. sort::distance) mapping to both, scalar and vectorial cell types.
 */
#define ASSERT_TYPE_EQUALITY(...)                                                                                   \
    static_assert(areSameType<__VA_ARGS__>(), ARGUMENTS_MUST_EQUAL)




/*
 * The intention of this macro is to lead to a guaranteed failure, since it is supposed to be used when
 * a parameter is of a vectorial cell type, although it must fit to the kernel's scalar cell type.
 */
#define FAIL_ON_PARAM_ASSUMING_SCALAR(T, V)                                                                     \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec2>()), FLOAT_PARAM_MATCH_VEC2);     \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec3>()), FLOAT_PARAM_MATCH_VEC3);     \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec4>()), FLOAT_PARAM_MATCH_VEC4);     \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec2>()), DOUBLE_PARAM_MATCH_VEC2);   \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec3>()), DOUBLE_PARAM_MATCH_VEC3);   \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec4>()), DOUBLE_PARAM_MATCH_VEC4);

/*
 * The intention of this macro is to lead to a guaranteed failure, since it is supposed to be used when
 * a parameter is of a scalar cell type, although it must fit to the kernel's vectorial cell type.
 */
#define FAIL_ON_PARAM_ASSUMING_VECTORIAL(V, T)                                                                  \
    static_assert( !(areSameCelltype<V, glm::tvec2>() && areSameType<T, float>()), VEC2_PARAM_MATCH_FLOAT);     \
    static_assert( !(areSameCelltype<V, glm::tvec2>() && areSameType<T, double>()), VEC2_PARAM_MATCH_DOUBLE);   \
    static_assert( !(areSameCelltype<V, glm::tvec3>() && areSameType<T, float>()), VEC3_PARAM_MATCH_FLOAT);     \
    static_assert( !(areSameCelltype<V, glm::tvec3>() && areSameType<T, double>()), VEC3_PARAM_MATCH_DOUBLE);   \
    static_assert( !(areSameCelltype<V, glm::tvec4>() && areSameType<T, float>()), VEC4_PARAM_MATCH_FLOAT);     \
    static_assert( !(areSameCelltype<V, glm::tvec4>() && areSameType<T, double>()), VEC4_PARAM_MATCH_DOUBLE);




/*
 * The intention of this macro is to lead to a guaranteed failure, since it is supposed to be used when
 * multiple parameters' types are not equal, although they must be homogeneous and fit to the kernel's scalar cell type.
 */
#define FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_SCALAR(T)                                                                  \
    static_assert( !areSameType<T, float>(),  PARAMS_EQUAL_MATCH_FLOAT);                                                \
    static_assert( !areSameType<T, double>(), PARAMS_EQUAL_MATCH_DOUBLE);

/*
 * The intention of this macro is to lead to a guaranteed failure, since it is supposed to be used when
 * multiple parameters' types are not equal, although they must be homogeneous and fit to the kernel's vectorial cell type.
 */
#define FAIL_ON_PARAM_HETEROGENEITY_ASSUMING_SCALAR_OR_VECTORIAL(T, V)                                                  \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec2>()),  PARAMS_EQUAL_MATCH_FLOAT_OR_VEC2);  \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec3>()),  PARAMS_EQUAL_MATCH_FLOAT_OR_VEC3);  \
    static_assert( !(areSameType<T, float>() && areSameCelltype<V, glm::tvec4>()),  PARAMS_EQUAL_MATCH_FLOAT_OR_VEC4);  \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec2>()), PARAMS_EQUAL_MATCH_DOUBLE_OR_VEC2); \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec3>()), PARAMS_EQUAL_MATCH_DOUBLE_OR_VEC3); \
    static_assert( !(areSameType<T, double>() && areSameCelltype<V, glm::tvec4>()), PARAMS_EQUAL_MATCH_DOUBLE_OR_VEC4);
