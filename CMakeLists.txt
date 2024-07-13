cmake_minimum_required(VERSION 3.29)
project(libxml2Perf)

option(ENABLE_TESTING "Enable Testing of performance improvements" ON)

set(BENCHMARK_START_SIZE 512)
math(EXPR DEFAULT_BENCHMARK_MAX_SIZE "1024 * 1024 * 256" OUTPUT_FORMAT DECIMAL)
set(BENCHMARK_MAX_SIZE ${DEFAULT_BENCHMARK_MAX_SIZE})
set(BENCHMARK_ITERATIONS 8)
set(BENCHMARK_NUM_THREADS 1)

set(CMAKE_CXX_STANDARD 23)
message("${CMAKE_PREFIX_PATH}")

find_package(libxml2 REQUIRED)
find_package(PkgConfig REQUIRED)
find_path(CPPCODEC_INCLUDE_DIR NAMES base64_default_rfc4648.hpp REQUIRED PATH_SUFFIXES include/cppcodec)
message(${CPPCODEC_INCLUDE_DIR})

add_subdirectory(lib)
add_subdirectory(benchmarks)

if (ENABLE_TESTING)
    add_subdirectory(tests)
endif()