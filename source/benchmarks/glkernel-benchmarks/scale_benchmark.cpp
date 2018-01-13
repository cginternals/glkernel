
#include <benchmark/benchmark.h>

#include <glkernel/Kernel.h>
#include <glkernel/scale.h>

static void BM_scale_quad(benchmark::State& state) {
    auto dkernel = glkernel::dkernel1{state.range(0), state.range(0)};


    for (auto _ : state)
        glkernel::scale::range(dkernel, -.5, .5, -1.0, 1.0);

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_scale_quad)->RangeMultiplier(2)->Range(8, 256)->Iterations(1)->Complexity();
