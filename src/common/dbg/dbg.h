#pragma once

#include <spdlog/spdlog.h>
#include <fmt/format.h>
#include <fmt/ostream.h>

namespace ICONation::Common::Dbg
{
    template <typename String, typename... Args>
    inline void info (const String &format_str, const Args & ... args) {
        spdlog::info (fmt::format (format_str, args ...));
    }

    template <typename String, typename... Args>
    inline void error (const String &format_str, const Args & ... args) {
        spdlog::error (fmt::format (format_str, args ...));
    }

    template <typename String, typename... Args>
    inline void warn (const String &format_str, const Args & ... args) {
        spdlog::warn (fmt::format (format_str, args ...));
    }

    inline void set_pattern (std::string pattern, spdlog::pattern_time_type time_type = spdlog::pattern_time_type::local) {
        spdlog::set_pattern (pattern, time_type);
    }
}