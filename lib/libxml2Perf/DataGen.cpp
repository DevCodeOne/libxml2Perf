#include "DataGen.h"

void base64Encode(std::string &str) {
    using base64 = cppcodec::base64_rfc4648;
    std::string encoded = base64::encode(str.data(), str.size());

    std::swap(str, encoded);
}