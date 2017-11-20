
#include <benchmark/benchmark.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/noise.h>

static void BM_gradientNoise_linear(benchmark::State& state) {
    auto dkernel = glkernel::dkernel1{state.range(0)};


    for (auto _ : state)
        glkernel::noise::gradient(dkernel, glkernel::noise::GradientNoiseType::Perlin);

    state.SetComplexityN(state.range(0));

}

static void BM_gradientNoise_quadratic(benchmark::State& state) {
    auto dkernel = glkernel::dkernel1{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::noise::gradient(dkernel, glkernel::noise::GradientNoiseType::Perlin);

    state.SetComplexityN(state.range(0));

}

static void BM_gradientNoise_cube(benchmark::State& state) {
    auto dkernel = glkernel::dkernel1{state.range(0), state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::noise::gradient(dkernel, glkernel::noise::GradientNoiseType::Perlin);

    state.SetComplexityN(state.range(0));

}
BENCHMARK(BM_gradientNoise_linear)->RangeMultiplier(2)->Range(2, 64)->Complexity();
BENCHMARK(BM_gradientNoise_quadratic)->RangeMultiplier(2)->Range(2, 64)->Complexity();
BENCHMARK(BM_gradientNoise_cube)->RangeMultiplier(2)->Range(2, 64)->Complexity();

BENCHMARK_MAIN();
