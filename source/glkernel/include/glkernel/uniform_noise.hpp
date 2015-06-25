#pragma once

#include <glkernel/uniform_noise.h>

#include <random>

#include <glkernel/glm_compatability.h>

namespace glkernel
{

template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
void uniform_noise(Kernel<T> & kernel, const T range_min, const T range_max)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::uniform_real_distribution<T> distribute(range_min, range_max);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = distribute(generator);
}

template <typename T, glm::precision P>
void uniform_noise(Kernel<glm::tvec2<T, P>> & kernel, const T range_min, const T range_max)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::uniform_real_distribution<T> distribute(range_min, range_max);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = glm::tvec2<T, P>(distribute(generator), distribute(generator));
}

template <typename T, glm::precision P>
void uniform_noise(Kernel<glm::tvec3<T, P>> & kernel, const T range_min, const T range_max)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::uniform_real_distribution<T> distribute(range_min, range_max);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = glm::tvec3<T, P>(distribute(generator), distribute(generator), distribute(generator));
}

template <typename T, glm::precision P>
void uniform_noise(Kernel<glm::tvec4<T, P>> & kernel, const T range_min, const T range_max)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::uniform_real_distribution<T> distribute(range_min, range_max);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = glm::tvec4<T, P>(distribute(generator), distribute(generator), distribute(generator), distribute(generator));
}

template <typename T, glm::precision P>
void uniform_noise(Kernel<glm::tvec2<T, P>> & kernel, const glm::tvec2<T, P> & range_min, const glm::tvec2<T, P> & range_max)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::uniform_real_distribution<T> distribute0(range_min[0], range_max[0]);
    std::uniform_real_distribution<T> distribute1(range_min[1], range_max[1]);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = glm::tvec2<T, P>(distribute0(generator), distribute1(generator));
}

template <typename T, glm::precision P>
void uniform_noise(Kernel<glm::tvec3<T, P>> & kernel, const glm::tvec3<T, P> & range_min, const glm::tvec3<T, P> & range_max)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::uniform_real_distribution<T> distribute0(range_min[0], range_max[0]);
    std::uniform_real_distribution<T> distribute1(range_min[1], range_max[1]);
    std::uniform_real_distribution<T> distribute2(range_min[2], range_max[2]);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = glm::tvec3<T, P>(distribute0(generator), distribute1(generator), distribute2(generator));
}

template <typename T, glm::precision P>
void uniform_noise(Kernel<glm::tvec4<T, P>> & kernel, const glm::tvec4<T, P> & range_min, const glm::tvec4<T, P> & range_max)
{
    std::random_device RD;
    std::mt19937_64 generator(RD());

    std::uniform_real_distribution<T> distribute0(range_min[0], range_max[0]);
    std::uniform_real_distribution<T> distribute1(range_min[1], range_max[1]);
    std::uniform_real_distribution<T> distribute2(range_min[2], range_max[2]);
    std::uniform_real_distribution<T> distribute3(range_min[3], range_max[3]);

    for (int i = 0; i < kernel.size(); ++i)
        kernel[i] = glm::tvec4<T, P>(distribute0(generator), distribute1(generator), distribute2(generator), distribute3(generator));
}

} // namespace glkernel
