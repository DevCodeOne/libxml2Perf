#include <gtest/gtest.h>

#include <libxml2Perf/DataGen.h>
#include <libxml2Perf/NodeWriter.h>

using ::testing::Test;


TEST(libxml2Perf, Basic_Comparison) {
    auto randomData = generateCyclicRandomData(32);
    auto randomData2 = generateCyclicRandomData(32);
    base64Encode(randomData);
    base64Encode(randomData2);

    const auto result1 = writerWithLibXml2(std::string(randomData));
    const auto otherResult = writerWithLibXml2(std::string(randomData2));

    const auto result2 = writerRaw(std::string(randomData));
    const auto result3 = writeRawToBuffer(std::string(randomData));
    const auto result4 = writeToBufferMemcpyWrapper(std::string(randomData));

    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, result3);
    EXPECT_EQ(result1, result4);
    EXPECT_NE(otherResult, result2);
    EXPECT_NE(otherResult, result3);
    EXPECT_NE(otherResult, result4);
}