
#include <benchmark/benchmark.h>

#include <glkernel/Kernel.h>
#include <glkernel/sort.h>

static void BM_sort_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel1{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::sort::distance(dkernel, {0});

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_sort_quad)->RangeMultiplier(2)->Range(8, 256)->Iterations(1)->Complexity();
