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




//template<typename T>
//struct is_cellType : std::false_type {};

//template<typename T, glm::precision P, template<typename, glm::precision> class V>
//struct is_cellType<V<T, P>> : std::true_type {};

//template<typename T, glm::precision P, template<typename, glm::precision> class V>
//constexpr bool isCellType() { return is_cellType<V<T, P>>::value; }

//template<typename T>
//constexpr bool isCellType() { return is_cellType<T>::value; }


//template<typename T>
//struct is_componenType : std::true_type {};

//template<typename T, glm::precision P, template<typename, glm::precision> class V>
//struct is_componenType<V<T, P>> : std::false_type {};

//template<typename T, glm::precision P, template<typename, glm::precision> class V>
//constexpr bool isComponentType() { return is_componenType<V<T, P>>::value; }

//template<typename T>
//constexpr bool isComponentType() { return is_componenType<T>::value; }




} // glkernel
