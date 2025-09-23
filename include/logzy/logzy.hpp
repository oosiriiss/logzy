#pragma once

#include <cstdint>
#include <format>
#include <print>
#include <source_location>
#include <string>

#include "logzy/formatters.hpp"
#include "logzy/logzy_export.hpp"

namespace logzy {
  namespace internal {
    LOGZY_NO_EXPORT enum class LogLevel : std::uint8_t {
      Info,
      Warning,
      Error,
      Debug,
      Critical
    };

    std::string formatLogLevel(LogLevel level);

    template <typename... Args>
    LOGZY_NO_EXPORT void log(LogLevel level,
                             const std::source_location sourceLoc,
                             std::format_string<Args...> fmt, Args &&...args) {
      auto formattedLevel = formatLogLevel(level);
      auto message = std::format(fmt, std::forward<Args>(args)...);

      auto fullPath = std::string(sourceLoc.file_name());

      std::println("{} {}({}:{}) | {}", formattedLevel,
                   fullPath.substr(fullPath.find_last_of('/') + 1),
                   sourceLoc.line(), sourceLoc.column(), message);
    }
  }  // namespace internal

  template <typename... Args>
  LOGZY_EXPORT inline void info(std::format_string<Args...> fmt, Args... args) {
    internal::log(internal::LogLevel::Info, std::source_location::current(),
                  fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  LOGZY_EXPORT inline void warn(std::format_string<Args...> fmt, Args... args) {
    internal::log(internal::LogLevel::Warning, std::source_location::current(),
                  fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  LOGZY_EXPORT inline void error(std::format_string<Args...> fmt,
                                 Args... args) {
    internal::log(internal::LogLevel::Error, std::source_location::current(),
                  fmt, std::forward<Args>(args)...);
  }

  // TODO :: Make this apply only in debug builds
  template <typename... Args>
  LOGZY_EXPORT inline void debug(std::format_string<Args...> fmt,
                                 Args... args) {
    internal::log(internal::LogLevel::Debug, std::source_location::current(),
                  fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  LOGZY_EXPORT inline void critical(std::format_string<Args...> fmt,
                                    Args... args) {
    internal::log(internal::LogLevel::Critical, std::source_location::current(),
                  fmt, std::forward<Args>(args)...);
  }

}  // namespace logzy
