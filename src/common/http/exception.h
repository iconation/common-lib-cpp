#pragma once

#include <exception>
#include <string>
#include <fmt/format.h>
#include <curl/curl.h>

namespace ICONation::Common::Http::Exception
{
    struct CurlError : public std::runtime_error {
        CurlError (const std::string &url, CURLcode code) throw() : 
            std::runtime_error (fmt::format("URL={} : Error={}", url, curl_easy_strerror(code))) {}
    };
}
