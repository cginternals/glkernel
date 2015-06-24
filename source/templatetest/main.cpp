
#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <initializer_list>

#include <QVector3D>
#include <glm/vec2.hpp>

// Everything floating point related (float, double)
template <typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
auto first(const T & val) -> decltype(val)
{
    return val;
}

// glm types
template <template<typename, glm::precision> class V, typename T, glm::precision P>
auto first(const V<T, P> & vec) -> decltype(vec.x)
{
    return vec.x;
}

// vector types without template parameter with a x() method
template <typename V>
auto first(const V & vec) -> decltype(vec.x())
{
    return vec.x();
}

// vector types without template parameter with a getX() method
template <typename V>
auto first(const V & vec) -> decltype(vec.getX())
{
    return vec.getX();
}

// vector types without template parameter with a x member
template <typename V>
auto first(const V & vec) -> decltype(vec.x)
{
    return vec.x;
}

// vector types with one template parameter with a x member
template <template<typename> class V, typename T>
auto first(const V<T> & vec) -> decltype(vec.x)
{
    return vec.x;
}

// c array type
template <typename T, typename std::enable_if<std::is_array<T>::value, int>::type = 0>
auto first(const T & value) -> decltype(value[0])
{
    return value[0];
}

// std::vector, std::list, ... (collection with two template parameters; type and allocator)
template <template<typename, typename> class V, typename T, typename A>
auto first(const V<T, A> & vec) -> decltype(vec.front())
{
    return vec.front();
}

// std::array, arbitrary template with type and size with a front() method
template <template<typename, unsigned long> class A, typename T, unsigned long C>
auto first(const A<T, C> & arr) -> decltype(arr.front())
{
    return arr.front();
}

// std::initializer_list,arbitrary type parameter collection with standard c++ iterators
template <template <typename> class L, typename T>
auto first(const L<T> & list) -> decltype(T(*list.begin()))
{
    if (list.size() == 0)
    {
        return 0;
    }

    return *list.begin();
}

struct MyVec
{
    int x() const { return 3; }
};

struct MyVec2
{
    int getX() const { return 4; }
};

template <typename T>
struct MyVec3
{
    MyVec3(T p_x) : x(p_x) {}

    T x;
};

struct MyVec4
{
    MyVec4(float p_x) : x(p_x) {}

    float x;
};

int main(int /*argc*/, char* /*argv*/[])
{
    double doubleArray[3] = { 1.0, 3.2, 6.5 };
    auto initializerList = {23.4, 54.1, 23.9};

    std::cout << first(3.2f) << std::endl;
    std::cout << first(glm::vec2(3, 2)) << std::endl;
    std::cout << first(QVector3D(3.3f, 1.0f, 3.2f)) << std::endl;
    std::cout << first(MyVec()) << std::endl;
    std::cout << first(MyVec2()) << std::endl;
    std::cout << first(MyVec3<int>(43)) << std::endl;
    std::cout << first(MyVec4(32.23f)) << std::endl;
    std::cout << first(doubleArray) << std::endl;
    std::cout << first(std::vector<char>({ 65, 42, 13 })) << std::endl;
    std::cout << first(std::array<int, 4>{{ 1, 2, 3, 4 }}) << std::endl;
    std::cout << first(std::list<bool>({ true, false, true })) << std::endl;
    std::cout << first(initializerList) << std::endl;

    return 0;
}
