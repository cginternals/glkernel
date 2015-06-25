#pragma once

#include <glkernel/normal_noise.h>

#include <random>

#include <glkernel/glm_compatability.h>

namespace glkernel
{

template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
void normal_noise(Kernel<T> & kernel, const T mean, const T stddev)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::normal_distribution<T> distribute(mean, stddev);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = distribute(generator);
}

template <typename T, glm::precision P>
void normal_noise(Kernel<glm::tvec2<T, P>> & kernel, const T mean, const T stddev)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::normal_distribution<T> distribute(mean, stddev);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = glm::tvec2<T, P>(distribute(generator), distribute(generator));
}

template <typename T, glm::precision P>
void normal_noise(Kernel<glm::tvec3<T, P>> & kernel, const T mean, const T stddev)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::normal_distribution<T> distribute(mean, stddev);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = glm::tvec3<T, P>(distribute(generator), distribute(generator), distribute(generator));
}

template <typename T, glm::precision P>
void normal_noise(Kernel<glm::tvec4<T, P>> & kernel, const T mean, const T stddev)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::normal_distribution<T> distribute(mean, stddev);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = glm::tvec4<T, P>(distribute(generator), distribute(generator), distribute(generator), distribute(generator));
}

template <typename T, glm::precision P>
void normal_noise(Kernel<glm::tvec2<T, P>> & kernel, const glm::tvec2<T, P> & mean, const glm::tvec2<T, P> & stddev)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::normal_distribution<T> distribute0(mean[0], stddev[0]);
    std::normal_distribution<T> distribute1(mean[1], stddev[1]);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = glm::tvec2<T, P>(distribute0(generator), distribute1(generator));
}

template <typename T, glm::precision P>
void normal_noise(Kernel<glm::tvec3<T, P>> & kernel, const glm::tvec3<T, P> & mean, const glm::tvec3<T, P> & stddev)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::normal_distribution<T> distribute0(mean[0], stddev[0]);
    std::normal_distribution<T> distribute1(mean[1], stddev[1]);
    std::normal_distribution<T> distribute2(mean[2], stddev[2]);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = glm::tvec3<T, P>(distribute0(generator), distribute1(generator), distribute2(generator));
}

template <typename T, glm::precision P>
void normal_noise(Kernel<glm::tvec4<T, P>> & kernel, const glm::tvec4<T, P> & mean, const glm::tvec4<T, P> & stddev)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::normal_distribution<T> distribute0(mean[0], stddev[0]);
    std::normal_distribution<T> distribute1(mean[1], stddev[1]);
    std::normal_distribution<T> distribute2(mean[2], stddev[2]);
    std::normal_distribution<T> distribute3(mean[3], stddev[3]);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = glm::tvec4<T, P>(distribute0(generator), distribute1(generator), distribute2(generator), distribute3(generator));
}

} // namespace glkernel
