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
    LOGZY_NO_EXPORT inline void log(LogLevel level,
                                    const std::source_location sourceLoc,
                                    std::format_string<Args...> fmt,
                                    Args &&...args) {
      auto formattedLevel = formatLogLevel(level);
      auto message = std::format(fmt, std::forward<Args>(args)...);

      // FIXME :: Possible slowdown?
      const auto f = std::string_view(sourceLoc.file_name());
      const auto filename = f.substr(f.find_last_of('/') + 1);

      std::println("{} {}({}:{}) | {}", formattedLevel, filename,
                   sourceLoc.line(), sourceLoc.column(), message);
    }
  }  // namespace internal

  template <typename... Args>
  LOGZY_EXPORT struct info {                             // NOLINT
    info(std::format_string<Args...> fmt, Args &&...ts,  // NOLINT
         std::source_location loc = std::source_location::current()) {
      internal::log(internal::LogLevel::Info, loc, fmt,
                    std::forward<Args>(ts)...);
    }
  };
  template <typename... Args>
  info(std::format_string<Args...> fmt, Args &&...args) -> info<Args...>;

  template <typename... Args>
  LOGZY_EXPORT struct warn {                             // NOLINT
    warn(std::format_string<Args...> fmt, Args &&...ts,  // NOLINT
         std::source_location loc = std::source_location::current()) {
      internal::log(internal::LogLevel::Warning, loc, fmt,
                    std::forward<Args>(ts)...);
    }
  };
  template <typename... Args>
  warn(std::format_string<Args...> fmt, Args &&...args) -> warn<Args...>;

  template <typename... Args>
  LOGZY_EXPORT struct error {                             // NOLINT
    error(std::format_string<Args...> fmt, Args &&...ts,  // NOLINT
          std::source_location loc = std::source_location::current()) {
      internal::log(internal::LogLevel::Error, loc, fmt,
                    std::forward<Args>(ts)...);
    }
  };
  template <typename... Args>
  error(std::format_string<Args...> fmt, Args &&...args) -> error<Args...>;

  template <typename... Args>
  LOGZY_EXPORT struct critical {                             // NOLINT
    critical(std::format_string<Args...> fmt, Args &&...ts,  // NOLINT
             std::source_location loc = std::source_location::current()) {
      internal::log(internal::LogLevel::Critical, loc, fmt,
                    std::forward<Args>(ts)...);
    }
  };
  template <typename... Args>
  critical(std::format_string<Args...> fmt, Args &&...args)
      -> critical<Args...>;

  // TODO :: Make this apply only in debug builds
  template <typename... Args>
  LOGZY_EXPORT struct debug {                             // NOLINT
    debug(std::format_string<Args...> fmt, Args &&...ts,  // NOLINT
          std::source_location loc = std::source_location::current()) {
      internal::log(internal::LogLevel::Debug, loc, fmt,
                    std::forward<Args>(ts)...);
    }
  };
  template <typename... Args>
  debug(std::format_string<Args...> fmt, Args &&...args) -> debug<Args...>;

}  // namespace logzy
