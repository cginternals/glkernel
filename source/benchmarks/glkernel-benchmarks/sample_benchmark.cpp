
#include <benchmark/benchmark.h>

#include <glkernel/Kernel.h>
#include <glkernel/sample.h>

static void BM_possion_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel2{state.range(0), state.range(0)};

    for (auto _ : state)
        glkernel::sample::poisson_square(dkernel);

    state.SetComplexityN(state.range(0));
}

static void BM_jittered_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel2{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::sample::multi_jittered(dkernel);

    state.SetComplexityN(state.range(0));
}

static void BM_rooks_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel2{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::sample::n_rooks(dkernel);

    state.SetComplexityN(state.range(0));
}

static void BM_stratified_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel2{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::sample::stratified(dkernel);

    state.SetComplexityN(state.range(0));
}

static void BM_hammersley_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel2{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::sample::hammersley(dkernel);

    state.SetComplexityN(state.range(0));
}

static void BM_hammersley_sphere_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel3{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::sample::hammersley_sphere(dkernel);

    state.SetComplexityN(state.range(0));
}

static void BM_halton_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel2{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::sample::halton(dkernel, 2, 3);

    state.SetComplexityN(state.range(0));
}

static void BM_halton_sphere_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel3{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::sample::halton_sphere(dkernel, 2, 3);

    state.SetComplexityN(state.range(0));
}

static void BM_best_candidate_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel3{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::sample::best_candidate(dkernel);

    state.SetComplexityN(state.range(0));
}

static void BM_golden_point_set_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel2{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::sample::golden_point_set(dkernel);

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_poisson_quad)->RangeMultiplier(2)->Range(2, 64)->Complexity();
BENCHMARK(BM_jittered_quad)->RangeMultiplier(2)->Range(2, 64)->Complexity();
BENCHMARK(BM_rooks_quad)->RangeMultiplier(2)->Range(2, 64)->Complexity();
BENCHMARK(BM_stratified_quad)->RangeMultiplier(2)->Range(2, 64)->Complexity();
BENCHMARK(BM_hammersley_quad)->RangeMultiplier(2)->Range(2, 64)->Complexity();
BENCHMARK(BM_hammersley_sphere_quad)->RangeMultiplier(2)->Range(2, 64)->Complexity();
BENCHMARK(BM_halton_quad)->RangeMultiplier(2)->Range(2, 64)->Complexity();
BENCHMARK(BM_halton_sphere_quad)->RangeMultiplier(2)->Range(2, 64)->Complexity();
BENCHMARK(BM_best_candidate_quad)->RangeMultiplier(2)->Range(2, 64)->Complexity();
BENCHMARK(BM_golden_point_set_quad)->RangeMultiplier(2)->Range(2, 64)->Complexity();
