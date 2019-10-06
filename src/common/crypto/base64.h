#pragma once

#include <string>
#include <vector>

namespace ICONation::Common::Crypto
{
class Base64
{
    // Allocators
public:
    Base64(void) = default;
    ~Base64(void) = default;

public:
    std::string encode(const std::vector<unsigned char> &buffer);
    std::vector<unsigned char> decode(const std::string &str);
};
} // namespace ICONation::Common::Crypto