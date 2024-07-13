#pragma once

#ifndef BENCHMARK_START_SIZE
    #define BENCHMARK_START_SIZE 1024
#endif
#ifndef BENCHMARK_MAX_SIZE
    #define BENCHMARK_MAX_SIZE 1024 * 1024 * 256
#endif
#ifndef BENCHMARK_ITERATIONS
    #define BENCHMARK_ITERATIONS 16
#endif
#ifndef BENCHMARK_NUM_THREADS
    #define BENCHMARK_NUM_THREADS 1
#endif

#include <cstddef>
#include <benchmark/benchmark.h>

constexpr inline size_t startSize = BENCHMARK_START_SIZE;
constexpr inline size_t maxSize = BENCHMARK_MAX_SIZE;
constexpr inline size_t iterations = BENCHMARK_ITERATIONS;
constexpr inline auto timeUnit = benchmark::kSecond;
constexpr inline size_t numThreads = BENCHMARK_NUM_THREADS;
