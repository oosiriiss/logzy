#pragma once

#include <cstdint>
#include <print>
#include <source_location>
#include <string>

#include "logzy/formatters.hpp"
#include "logzy/logzy_export.hpp"
#include "rainbowcpp/colors.hpp"
#include "rainbowcpp/rainbowcpp.hpp"

namespace logzy {
  namespace internal {
    enum class LogLevel : std::uint8_t {
      Info,
      Warning,
      Error,
      Debug,
      Critical
    };

    constexpr std::string_view toString(const LogLevel level) {
      switch (level) {
        case LogLevel::Info:
          return "INFO";
        case LogLevel::Warning:
          return "WARNING";
        case LogLevel::Error:
          return "ERROR";
        case LogLevel::Debug:
          return "DEBUG";
        case LogLevel::Critical:
          return "CRITICAL";
      }
      std::unreachable();
    }

    constexpr std::string_view textColor(const LogLevel level) {
      using Fg = rainbow::colors::bit4::Foreground;
      using Bg = rainbow::colors::bit4::Background;

      switch (level) {
        case LogLevel::Debug:
          return rainbow::color<Fg::Gray, Bg::Black>();
        case LogLevel::Info:
          return rainbow::color<Fg::Blue, Bg::Black>();
        case LogLevel::Warning:
          return rainbow::color<Fg::Yellow, Bg::Black>();
        case LogLevel::Error:
          return rainbow::color<Fg::Red, Bg::Black>();
        case LogLevel::Critical:
          return rainbow::color<Fg::Black, Bg::Red>();
      }

      std::unreachable();
    }

    constexpr std::string formatLogLevel(const LogLevel level) {
      const std::string_view levelStr = toString(level);
      const std::string_view color = textColor(level);
      constexpr std::string_view reset = rainbow::reset();

      return std::format("{}[{}]{}", color, levelStr, reset);
    }

    template <typename... Args>
    inline void log(LogLevel level, const std::source_location sourceLoc,
                    std::format_string<Args...> fmt, Args &&...args) {
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
  struct info {                                          // NOLINT
    info(std::format_string<Args...> fmt, Args &&...ts,  // NOLINT
         std::source_location loc = std::source_location::current()) {
      internal::log(internal::LogLevel::Info, loc, fmt,
                    std::forward<Args>(ts)...);
    }
  };
  template <typename... Args>
  info(std::format_string<Args...> fmt, Args &&...args) -> info<Args...>;

  template <typename... Args>
  struct warn {                                          // NOLINT
    warn(std::format_string<Args...> fmt, Args &&...ts,  // NOLINT
         std::source_location loc = std::source_location::current()) {
      internal::log(internal::LogLevel::Warning, loc, fmt,
                    std::forward<Args>(ts)...);
    }
  };
  template <typename... Args>
  warn(std::format_string<Args...> fmt, Args &&...args) -> warn<Args...>;

  template <typename... Args>
  struct error {                                          // NOLINT
    error(std::format_string<Args...> fmt, Args &&...ts,  // NOLINT
          std::source_location loc = std::source_location::current()) {
      internal::log(internal::LogLevel::Error, loc, fmt,
                    std::forward<Args>(ts)...);
    }
  };
  template <typename... Args>
  error(std::format_string<Args...> fmt, Args &&...args) -> error<Args...>;

  template <typename... Args>
  struct critical {                                          // NOLINT
    critical(std::format_string<Args...> fmt, Args &&...ts,  // NOLINT
             std::source_location loc = std::source_location::current()) {
      internal::log(internal::LogLevel::Critical, loc, fmt,
                    std::forward<Args>(ts)...);
    }
  };
  template <typename... Args>
  critical(std::format_string<Args...> fmt, Args &&...args)
      -> critical<Args...>;

#ifdef LOGZY_DISABLE_DEBUG_LOGS

  template <typename... Args>
  struct debug {      // NOLINT
    constexpr debug(  // NOLINT
        [[maybe_unused]] std::format_string<Args...> fmt,
        [[maybe_unused]] Args &&...args) noexcept {}
  };

#else
  template <typename... Args>
  struct debug {                                          // NOLINT
    debug(std::format_string<Args...> fmt, Args &&...ts,  // NOLINT
          std::source_location loc = std::source_location::current()) {
      internal::log(internal::LogLevel::Debug, loc, fmt,
                    std::forward<Args>(ts)...);
    }
  };
  template <typename... Args>
  debug(std::format_string<Args...> fmt, Args &&...args) -> debug<Args...>;

#endif

}  // namespace logzy
