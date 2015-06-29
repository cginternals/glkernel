#pragma once

#include <glm/gtc/type_precision.hpp>

#include <glkernel/kernel.h>


namespace glkernel
{

class sample
{
    sample() = delete;

public:

    // POISSON DISK SAMPLING WITHIN A SQUARE (TILABLE)

    // returns number of actual generated points (note: this number is between 0 and kernel.size)

    // guess a good number that targets the actual generated number of points generated to match kernel.size
    template <typename T, glm::precision P>
    static size_t poisson_square(tkernel<glm::tvec2<T, P>> & kernel, unsigned int num_probes = 32);

    // in contrast to the typical default impl. this impl uses the best of num_probes, randomizes the actives, ...
    template <typename T, glm::precision P>
    static size_t poisson_square(tkernel<glm::tvec2<T, P>> & kernel, T min_dist, unsigned int num_probes = 32);

private:
    template <typename T, glm::precision P>
    struct PoissonSquareMap;
};

} // namespace glkernel

#include <glkernel/sample.hpp>
