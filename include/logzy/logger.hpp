#pragma once

#include <format>
#include <iostream>
#include <rainbowcpp/rainbowcpp.hpp>
#include <source_location>
#include <string_view>
#include <type_traits>
#include <utility>

#include "log_level.hpp"
#include "logzy/filter.hpp"

namespace logzy {

  namespace internal {
    template <typename... Args>
    struct log_meta {  // NOLINT(readability-identifier-naming)
      std::format_string<Args...> fmt;
      std::source_location loc;

      template <typename StringType>
        requires std::is_constructible_v<std::format_string<Args...>,
                                         StringType>
      consteval log_meta(  // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
          StringType fmt,
          std::source_location loc = std::source_location::current()) noexcept
          : fmt{fmt},
            loc{loc} {}
    };

  }  // namespace internal
  template <typename... Args>
  using log_format = std::type_identity_t<internal::log_meta<Args...>>;

#define LOG_METHOD(METHOD_NAME, /*NOLINT(cppcoreguidelines-macro-usage)*/ \
                   METHOD_LOG_LEVEL)                                      \
  template <typename... Args>                                             \
  inline void METHOD_NAME(log_format<Args...> format, Args&&... args) {   \
    log<METHOD_LOG_LEVEL, Args...>(format, std::forward<Args>(args)...);  \
  }

  struct Logger {
    template <LogLevel Level, typename... Args>
    inline void log(log_format<Args...> format, Args&&... args);

    template <typename... Args>
    inline void log(LogLevel level, const std::source_location& sourceLoc,
                    std::format_string<Args...> fmt, Args&&... args);

    LOG_METHOD(trace, LogLevel::Trace);
    LOG_METHOD(debug, LogLevel::Debug);
    LOG_METHOD(info, LogLevel::Info);
    LOG_METHOD(warn, LogLevel::Warning);
    LOG_METHOD(error, LogLevel::Error);
    LOG_METHOD(critical, LogLevel::Critical);

    [[nodiscard]] static constexpr auto textColor(LogLevel level)
        -> std::string_view;

    [[nodiscard]] static constexpr auto formatLogLevel(LogLevel level)
        -> std::string;

    std::unique_ptr<LogFilter> filter{nullptr};
  };

#undef LOG_METHOD

  template <LogLevel Level, typename... Args>
  inline void Logger::log(log_format<Args...> format, Args&&... args) {
    if constexpr (std::to_underlying(Level) <
                  std::to_underlying(internal::COMP_MIN_LOG_LEVEL)) {
      return;
    }

    log(Level, format.loc, format.fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  inline void Logger::log(LogLevel level, const std::source_location& sourceLoc,
                          std::format_string<Args...> fmt, Args&&... args) {
    const auto formattedLevel = formatLogLevel(level);
    const auto message = std::format(fmt, std::forward<Args>(args)...);

    // FIXME :: Possible slowdown?
    const auto filePath = std::string_view(sourceLoc.file_name());
    const auto fileName = filePath.substr(filePath.find_last_of('/') + 1);

    if (filter != nullptr) {
      const bool messagePassedFilters = filter->filterFile(fileName) &&
                                        filter->filterLevel(level) &&
                                        filter->filterMessage(message);
      if (!messagePassedFilters) {
        return;
      }
    }

    std::cout << formattedLevel << ' ';
    std::cout << fileName << '(' << sourceLoc.line() << ','
              << sourceLoc.column() << ") | ";
    std::cout << message << '\n';
  }

  constexpr std::string_view Logger::textColor(const LogLevel level) {
    using Fg = rainbow::colors::bit4::Foreground;
    using Bg = rainbow::colors::bit4::Background;

    switch (level) {
      case LogLevel::Trace:
        return rainbow::color<rainbow::Color(64, 64, 64),  // NOLINT
                              Bg::Default>();
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

  constexpr std::string Logger::formatLogLevel(const LogLevel level) {
    const std::string_view levelStr = internal::toString(level);
    const std::string_view color = textColor(level);
    constexpr std::string_view reset = rainbow::reset();

    std::string buffer;
    constexpr size_t safetyBuffer = 8;
    buffer.reserve(levelStr.length() + color.length() + reset.length() +
                   safetyBuffer);

    buffer += color;
    buffer.push_back('[');
    buffer += levelStr;
    buffer.push_back(']');
    buffer += reset;

    return buffer;
  }
}  // namespace logzy
