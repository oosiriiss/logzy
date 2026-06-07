#pragma once

#include "logzy/log_level.hpp"
namespace logzy {
  struct LogFilter {
    LogFilter() = default;
    virtual ~LogFilter() = default;

    LogFilter(const LogFilter&) = default;
    LogFilter(LogFilter&&) = default;
    LogFilter& operator=(const LogFilter&) = default;
    LogFilter& operator=(LogFilter&&) = default;

    constexpr virtual auto filterLevel([[maybe_unused]] LogLevel level)
        -> bool {
      return true;
    }
    constexpr virtual auto filterFile(
        [[maybe_unused]] std::string_view fileName) -> bool {
      return true;
    }

    constexpr virtual auto filterMessage(
        [[maybe_unused]] std::string_view logMessage) -> bool {
      return true;
    }
  };
}  // namespace logzy
