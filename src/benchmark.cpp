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

static void bench_uintset(benchmark::State& state) {
    for (auto _ : state) {
        unit x;
        uint_set(&x, 0);
    }
}
BENCHMARK(bench_uintset);

static void bench_uintbit(benchmark::State& state) {
    unit x;
    uint_set(&x, 0);
    for (auto _ : state) {
        uint_bit(&x, 0);
    }
}
BENCHMARK(bench_uintbit);

static void bench_uintadd3(benchmark::State& state) {
    unit x, y, z;
    uint_set(&x, 0);
    uint_set(&y, 0);
    uint_set(&z, 0);
    for (auto _ : state) {
        uint_add3(&x, &y, &z);
    }
}
BENCHMARK(bench_uintadd3);

static void bench_uintsub3(benchmark::State& state) {
    unit x, y, z;
    uint_set(&x, 0);
    uint_set(&y, 0);
    uint_set(&z, 0);
    for (auto _ : state) {
        uint_sub3(&x, &y, &z);
    }
}
BENCHMARK(bench_uintsub3);

static void bench_uintmul3_64(benchmark::State& state) {
    unit x, y;
    uint_set(&x, 0);
    uint_set(&y, 0);
    for (auto _ : state) {
        uint_mul3_64(&x, &y, 0);
    }
}
BENCHMARK(bench_uintmul3_64);


BENCHMARK_MAIN();
