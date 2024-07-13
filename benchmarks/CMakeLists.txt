add_executable(libxml2Perf
            Benchmarks.cpp
            BenchmarkValues.h)

find_package(benchmark REQUIRED)

target_link_libraries(libxml2Perf PRIVATE benchmark::benchmark)
target_link_libraries(libxml2Perf PRIVATE libxml2PerfLib)
target_compile_definitions(libxml2Perf PRIVATE BENCHMARK_START_SIZE=${BENCHMARK_START_SIZE})
target_compile_definitions(libxml2Perf PRIVATE BENCHMARK_MAX_SIZE=${BENCHMARK_MAX_SIZE})
target_compile_definitions(libxml2Perf PRIVATE BENCHMARK_ITERATIONS=${BENCHMARK_ITERATIONS})
target_compile_definitions(libxml2Perf PRIVATE BENCHMARK_NUM_THREADS=${BENCHMARK_NUM_THREADS})
