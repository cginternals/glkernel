
#include <benchmark/benchmark.h>


#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/shuffle.h>

static void BM_permutation_linear(benchmark::State& state) {
    auto dkernel = glkernel::dkernel1{state.range(0)};


    for (auto _ : state)
        glkernel::shuffle::bucket_permutate(dkernel, state.range(0)/2, 1, 1, true);

    state.SetComplexityN(state.range(0));

}

static void BM_permutation_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel1{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::shuffle::bucket_permutate(dkernel, state.range(0)/2, state.range(0)/2, 1, true);

    state.SetComplexityN(state.range(0));

}

static void BM_bayer_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel1{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::shuffle::bayer(dkernel);

    state.SetComplexityN(state.range(0));

}

static void BM_random_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel1{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::shuffle::random(dkernel);

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_permutation_quad)->RangeMultiplier(2)->Range(8, 256)->Iterations(1)->Complexity();
BENCHMARK(BM_bayer_quad)->RangeMultiplier(2)->Range(8, 256)->Iterations(1)->Complexity();
