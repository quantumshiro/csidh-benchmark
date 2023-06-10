#include "../benchmark/include/benchmark/benchmark.h"

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
}

void uint_print(const unit* x)
{
    for (size_t i = 8 * LIMBS; i != SIZE_MAX; --i)
        std::cout << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>((reinterpret_cast<const unsigned char*>(x->c))[i]);
}

void fp_print(const fp* x)
{
    unit y;
    fp_dec(&y, x);
    uint_print(&y);
}

static void create_keys(benchmark::State& state) {
    private_key priv_alice;

    for (auto _ : state) {
        csidh_private(&priv_alice);
    }
}

BENCHMARK(create_keys);
