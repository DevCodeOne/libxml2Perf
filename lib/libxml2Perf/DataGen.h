#pragma once

#include <array>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>

#include <base64_default_rfc4648.hpp>

#include <libxml2/libxml/xmlwriter.h>

void base64Encode(std::string &str);

template<unsigned int PoolSize = 512>
std::string generateCyclicRandomData(size_t size) requires (PoolSize < 1024) {
    std::array<char, PoolSize> randomPool{};

    std::ranges::transform(randomPool.begin(), randomPool.end(), randomPool.begin(), [](const auto &ele) {
        return static_cast<std::decay_t<decltype(ele)>>(std::rand());
    });

    std::string randomData;
    randomData.reserve(size);

    size_t currentElement = 0;
    for (size_t i = 0; i < size; ++i) {
        randomData.push_back(randomPool[currentElement++]);
        if (currentElement >= randomPool.size()) {
            currentElement = std::rand() % randomPool.size();
        }
    }

    return std::move(randomData);
}