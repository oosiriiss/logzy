#include "logzy/logzy.hpp"

#include <format>
#include <string>
#include <string_view>
#include <utility>

namespace {
  using logzy::internal::LogLevel;
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
        return "Critical";
    }
    std::unreachable();
  }

  // Returns a string that will allow the output of a colored text to the
  // terminal.
  // Ansi Color codes
  // https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit
  constexpr std::string_view textColor(const LogLevel level) {
    // TODO :: Add more support for colored output
    const auto fgRedBgBlack = std::string_view("\033[31;40m");
    const auto fgCyanBgBlack = std::string_view("\033[36;40m");
    const auto fgYellowBgBlack = std::string_view("\033[33;40m");
    const auto fgGrayBgBlack = std::string_view("\033[90;40m");
    const auto fgBlackBgRed = std::string_view("\033[41;30m");

    switch (level) {
      case LogLevel::Info:
        return fgCyanBgBlack;
      case LogLevel::Warning:
        return fgYellowBgBlack;
      case LogLevel::Error:
        return fgRedBgBlack;
      case LogLevel::Debug:
        return fgGrayBgBlack;
      case LogLevel::Critical:
        return fgBlackBgRed;
    }

    std::unreachable();
  }

  constexpr std::string_view textColorEnd() {
    const auto ansiResetcode = std::string_view("\033[39;49m");
    return ansiResetcode;
  }

}  // namespace

std::string logzy::internal::formatLogLevel(const LogLevel level) {
  const std::string_view levelStr = toString(level);
  const std::string_view color = textColor(level);
  const std::string_view colorEnd = textColorEnd();

  return std::format("[{}{}{}]", color, levelStr, colorEnd);
}
