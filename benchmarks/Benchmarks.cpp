#include "BenchmarkValues.h"

#include <libxml2Perf/DataGen.h>
#include <libxml2Perf/NodeWriter.h>

#include <benchmark/benchmark.h>

class RandomDataFixture : public benchmark::Fixture {
public:
    void SetUp(::benchmark::State& state) override {
        randomData = generateCyclicRandomData(state.range(0));
    }

    void TearDown(::benchmark::State& state) override {
    }

    std::string randomData;
};

BENCHMARK_DEFINE_F(RandomDataFixture, writeXml)(benchmark::State &state) {
    for (auto _ : state) {
        const auto result = writerWithLibXml2(randomData);
    }
}

BENCHMARK_DEFINE_F(RandomDataFixture, writeBufferStr)(benchmark::State &state) {
    for (auto _ : state) {
        const auto result = writeRawToBuffer(randomData);
    }
}

BENCHMARK_DEFINE_F(RandomDataFixture, writeXmlWithStrStream)(benchmark::State& state) {
    for (auto _ : state) {
        const auto result = writerRaw(randomData);
    }
}

BENCHMARK_DEFINE_F(RandomDataFixture, writeXmlWithMemcpyWrapper)(benchmark::State& state) {
    for (auto _ : state) {
        const auto result = writeToBufferMemcpyWrapper(std::move(randomData));
    }
}

BENCHMARK_REGISTER_F(RandomDataFixture, writeXml)->Range(startSize, maxSize)
    ->Iterations(iterations)
    ->Unit(timeUnit)
    ->Threads(numThreads);
BENCHMARK_REGISTER_F(RandomDataFixture, writeBufferStr)->Range(startSize, maxSize)
    ->Iterations(iterations)
    ->Unit(timeUnit)
    ->Threads(numThreads);
BENCHMARK_REGISTER_F(RandomDataFixture, writeXmlWithStrStream)->Range(startSize, maxSize)
    ->Iterations(iterations)
    ->Unit(timeUnit)
    ->Threads(numThreads);
BENCHMARK_REGISTER_F(RandomDataFixture, writeXmlWithMemcpyWrapper)->Range(startSize, maxSize)
    ->Iterations(iterations)
    ->Unit(timeUnit)
    ->Threads(numThreads);

BENCHMARK_MAIN();
