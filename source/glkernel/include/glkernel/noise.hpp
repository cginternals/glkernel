#pragma once

#include <glkernel/noise.h>

#include <random>

#include <glkernel/glm_compatability.h>


namespace glkernel
{

    /* // ToDo: might be simplified by using per componant iterator with applied lambda expression ...
        auto kernel = fkernel2{ 1024 };

        noise::uniform(kernel, 0.0, 1.0);
        kernel.apply([](){ fooo:; });

        kernel::map<noise::_uniform>(kernel, 0.0, 1.0)
        {
            auto foo = noise::uniform(kernel, 0.0, 1.0);
        }

        class uniform
        {
            void operator()(kernel & k)
        };

        kernel::iterate_coefficient(noise::uniform(0.0, 1.0), kernel);
    */

template <typename T>
inline void noise::normal_base(T * kernel, const size_t size, const T mean, const T stddev, const size_t step, const size_t offset)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::normal_distribution<T> distribute(mean, stddev);

    for (int i = 0; i < size; ++i)
        kernel[i * step + offset] = distribute(generator);
}

template <typename T, int C>
inline void noise::normal_base(T * kernel, const size_t size, const T mean, const T stddev)
{
    for (int c = 0; c < C; ++c)
        normal_base<T>(kernel, size, mean, stddev, C, c);
}

template <typename T, int C>
inline void noise::normal_base(T * kernel, const size_t size, const T * mean, const T * stddev)
{ 
    for (size_t c = 0; c < C; ++c)
        normal_base<T>(kernel, size, mean[c], stddev[c], C, c);
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type>
void noise::normal(tkernel<T> & kernel, const T mean, const T stddev)
{
    normal_base<T, 1>(const_cast<T *>(kernel.data()), kernel.size(), mean, stddev);
}
template <typename T, glm::precision P, template<typename, glm::precision> class V>
void noise::normal(tkernel<V<T, P>> & kernel, const T mean, const T stddev)
{
    normal_base<T, sizeof(V<T, P>) / sizeof(V<T, P>::value_type)>(
        const_cast<T *>(kernel.data()), kernel.size(), mean, stddev);
}
template <typename T, glm::precision P, template<typename, glm::precision> class V>
void noise::normal(tkernel<V<T, P>> & kernel, const V<T, P> & mean, const V<T, P> & stddev)
{
    normal_base<T, sizeof(V<T, P>) / sizeof(V<T, P>::value_type)>(
        const_cast<T *>(kernel.data()), kernel.size(), glm::value_ptr(mean), glm::value_ptr(stddev));
}

// UNIFORM

template <typename T>
inline void noise::uniform_base(T * kernel, const size_t size, const T range_min, const T range_max, const size_t step, const size_t offset)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::uniform_real_distribution<T> distribute(range_min, range_max);

    for (int i = 0; i < size; ++i)
        kernel[i * step + offset] = distribute(generator);
}

template <typename T, int C>
inline void noise::uniform_base(T * kernel, const size_t size, const T range_min, const T range_max)
{
    for (int c = 0; c < C; ++c)
        uniform_base<T>(kernel, size, range_min, range_max, C, c);
}

template <typename T, int C>
inline void noise::uniform_base(T * kernel, const size_t size, const T * range_min, const T * range_max)
{
    for (size_t c = 0; c < C; ++c)
        uniform_base<T>(kernel, size, range_min[c], range_max[c], C, c);
}


template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type>
void noise::uniform(tkernel<T> & kernel, const T range_min, const T range_max)
{
    uniform_base<T, 1>(const_cast<T *>(kernel.data()), kernel.size(), range_min, range_max);
}
template <typename T, glm::precision P>
void noise::uniform(tkernel<glm::tvec2<T, P>> & kernel, const T range_min, const T range_max)
{
    uniform_base<T, 2>(const_cast<T *>(kernel.data()), kernel.size(), range_min, range_max);
}
template <typename T, glm::precision P>
void noise::uniform(tkernel<glm::tvec3<T, P>> & kernel, const T range_min, const T range_max)
{
    uniform_base<T, 3>(const_cast<T *>(kernel.data()), kernel.size(), range_min, range_max);
}
template <typename T, glm::precision P>
void noise::uniform(tkernel<glm::tvec4<T, P>> & kernel, const T range_min, const T range_max)
{
    uniform_base<T, 4>(const_cast<T *>(kernel.data()), kernel.size(), range_min, range_max);
}
template <typename T, glm::precision P>
void noise::uniform(tkernel<glm::tvec2<T, P>> & kernel, const glm::tvec2<T, P> & range_min, const glm::tvec2<T, P> & range_max)
{
    uniform_base<T, 2>(const_cast<T *>(kernel.data()), kernel.size(), glm::value_ptr(range_min), glm::value_ptr(range_max));
}
template <typename T, glm::precision P>
void noise::uniform(tkernel<glm::tvec3<T, P>> & kernel, const glm::tvec3<T, P> & range_min, const glm::tvec3<T, P> & range_max)
{
    uniform_base<T, 3>(const_cast<T *>(kernel.data()), kernel.size(), glm::value_ptr(range_min), glm::value_ptr(range_max));
}
template <typename T, glm::precision P>
void noise::uniform(tkernel<glm::tvec4<T, P>> & kernel, const glm::tvec4<T, P> & range_min, const glm::tvec4<T, P> & range_max)
{
    uniform_base<T, 4>(const_cast<T *>(kernel.data()), kernel.size(), glm::value_ptr(range_min), glm::value_ptr(range_max));
}

} // namespace glkernel
