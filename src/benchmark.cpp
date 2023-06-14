#include <benchmark/benchmark.h>

#include <iostream>
#include <vector>
#include <chrono>
#include <cassert>
#include <iomanip>
#include <cstring>
#include <string>

extern "C" {
    #include "include/fp.h"
    #include "include/csidh.h"
    #include "include/params.h"
    #include "include/mont.h"
    #include "include/rng.h"
    #include "include/uint.h"
}

static void bench_RandomBytes(benchmark::State& state) {
    for (auto _ : state) {
        uint8_t x[32];
        randombytes(x, 32);
    }
}

BENCHMARK(bench_RandomBytes);


BENCHMARK_MAIN();
