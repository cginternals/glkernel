#pragma once

#include <iostream>
#include <glkernel/Kernel.h>



namespace glkernel
{



template<typename... T>
struct are_same_type : std::false_type { };

template<>
struct are_same_type<> : std::true_type { };

template<typename T>
struct are_same_type<T> : std::true_type { };

template<typename T, typename... Ts>
struct are_same_type<T, T, Ts...> : are_same_type<T, Ts...> { };

template<typename... T>
constexpr bool areSameType() { return are_same_type<T...>::value; }




template<template<typename, glm::precision> class... Vs>
struct are_same_celltype : std::false_type { };

template<>
struct are_same_celltype<> : std::true_type { };

template<template<typename, glm::precision> class V>
struct are_same_celltype<V> : std::true_type { };

template<template<typename, glm::precision> class V, template<typename, glm::precision> class... Vs>
struct are_same_celltype<V, V, Vs...> : are_same_celltype<V, Vs...> { };

template<template<typename, glm::precision> class... Vs>
constexpr bool areSameCelltype() { return are_same_celltype<Vs...>::value; }




template<typename T>
struct is_celltype : std::false_type {};

template<typename T, glm::precision P, template<typename, glm::precision> class V>
struct is_celltype<V<T, P>> : std::true_type {};

template<typename T, glm::precision P, template<typename, glm::precision> class V>
constexpr bool isCelltype() { return is_celltype<V<T, P>>::value; }




template< typename T >
struct always_false : std::false_type {};


template<typename T>
struct is_templateTemplate : std::false_type {};

template<typename... T, template<typename...> class V>
struct is_templateTemplate<V<T...>> : std::true_type {};

template<typename... T, template<typename...> class V>
constexpr bool isTemplateTemplate() { return is_templateTemplate<V<T...>>::value; }

template<typename... T, template<typename...> class V>
constexpr bool isPureTemplate() { return !is_templateTemplate<V<T...>>::value; }

template<typename T>
constexpr bool isTemplateTemplate() { return is_templateTemplate<T>::value; }

template<typename T>
constexpr bool isPureTemplate() { return !is_templateTemplate<T>::value; }




} // glkernel
