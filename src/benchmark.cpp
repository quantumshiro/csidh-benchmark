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

// benchmark fp
static void bench_fp_set(benchmark::State& state) {
    fp x;
    for (auto _ : state) {
        fp_set(&x, 0);
    }
}
BENCHMARK(bench_fp_set);

static void bench_fp_add3(benchmark::State& state) {
    fp x, y, z;
    fp_set(&x, 0);
    fp_set(&y, 0);
    fp_set(&z, 0);
    for (auto _ : state) {
        fp_add3(&x, &y, &z);
    }
}
BENCHMARK(bench_fp_add3);

static void bench_fp_sub3(benchmark::State& state) {
    fp x, y, z;
    fp_set(&x, 0);
    fp_set(&y, 0);
    fp_set(&z, 0);
    for (auto _ : state) {
        fp_sub3(&x, &y, &z);
    }
}
BENCHMARK(bench_fp_sub3);

static void bench_fp_mul3(benchmark::State& state) {
    fp x, y, z;
    fp_set(&x, 0);
    fp_set(&y, 0);
    fp_set(&z, 0);
    for (auto _ : state) {
        fp_mul3(&x, &y, &z);
    }
}
BENCHMARK(bench_fp_mul3);

static void bench_fp_sq1(benchmark::State& state) {
    fp x;
    fp_set(&x, 0);
    for (auto _ : state) {
        fp_sq1(&x);
    }
}
BENCHMARK(bench_fp_sq1);

static void bench_fp_sq2(benchmark::State& state) {
    fp x, y;
    fp_set(&x, 0);
    fp_set(&y, 0);
    for (auto _ : state) {
        fp_sq2(&x, &y);
    }
}
BENCHMARK(bench_fp_sq2);

static void bench_fp_inv(benchmark::State& state) {
    fp x;
    fp_set(&x, 0);
    for (auto _ : state) {
        fp_inv(&x);
    }
}
BENCHMARK(bench_fp_inv);

static void bench_fp_issquare(benchmark::State& state) {
    fp x;
    fp_set(&x, 0);
    for (auto _ : state) {
        fp_issquare(&x);
    }
}
BENCHMARK(bench_fp_issquare);

static void bench_fp_random(benchmark::State& state) {
    fp x;
    for (auto _ : state)
    {
        fp_random(&x);
    }
}
BENCHMARK(bench_fp_random);

// benchmark mont
static void bench_mont_XDBL(benchmark::State& state) {
    proj Q, A, P;
    fp_random(&A.x);
    fp_random(&A.z);
    fp_random(&P.x);
    fp_random(&P.z);
    for (auto _ : state) {
        xDBL(&Q, &A, &P);
    }
}
BENCHMARK(bench_mont_XDBL);

static void bench_mont_XADD(benchmark::State& state) {
    proj S, P, Q, PQ;
    fp_random(&S.x);
    fp_random(&S.z);
    fp_random(&P.x);
    fp_random(&P.z);
    fp_random(&Q.x);
    fp_random(&Q.z);
    for (auto _ : state) {
        xADD(&PQ, &S, &P, &Q);
    }
}
BENCHMARK(bench_mont_XADD);

static void bench_mont_XDBLADD(benchmark::State& state) {
    proj S, P, Q, PQ, A, B;
    fp_random(&S.x);
    fp_random(&S.z);
    fp_random(&P.x);
    fp_random(&P.z);
    fp_random(&Q.x);
    fp_random(&Q.z);
    fp_random(&A.x);
    fp_random(&A.z);
    fp_random(&B.x);
    fp_random(&B.z);
    for (auto _ : state) {
        xDBLADD(&PQ, &S, &P, &Q, &A, &B);
    }
}
BENCHMARK(bench_mont_XDBLADD);

static void bench_mont_XMUL(benchmark::State& state) {
    proj a, b, c;
    unit d;
    fp_random(&a.x);
    fp_random(&a.z);
    fp_random(&b.x);
    fp_random(&b.z);
    for (auto _ : state) {
        xMUL(&c, &a, &b, &d);
    }
}
BENCHMARK(bench_mont_XMUL);

static void bench_mont_ISOG(benchmark::State& state) {
    proj P, Q, R;
    uint64_t k = 3;
    fp_random(&P.x);
    fp_random(&P.z);
    fp_random(&Q.x);
    fp_random(&Q.z);

    for (auto _ : state) {
        xISOG(&R, &P, &Q, k);
    }
}
BENCHMARK(bench_mont_ISOG);
BENCHMARK_MAIN();
