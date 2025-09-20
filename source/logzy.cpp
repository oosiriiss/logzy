#include "logzy/logzy.hpp"

#include <iostream>
#include <string>
#include <string_view>
#include <source_location>
#include <format>

namespace {
  using logzy::LogLevel;

  constexpr std::string_view ToString(const LogLevel level) {
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
  }

  // Returns a string that will allow the output of a colored text to the
  // terminal.
  // Ansi Color codes
  // https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit
  constexpr std::string_view TextColor(const LogLevel level) {
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
  }

  constexpr std::string_view TextColorEnd() {
    const auto ansiResetcode = std::string_view("\033[39;49m");
    return ansiResetcode;
  }

  constexpr std::string FormatLogLevel(const LogLevel level) {
    const std::string_view levelStr = ToString(level);
    const std::string_view color = TextColor(level);
    const std::string_view colorEnd = TextColorEnd();

    return std::format("[{}{}{}]", color, levelStr, colorEnd);
  }
}  // namespace

namespace logzy {
  void Log(LogLevel level, const std::string &message,
           const std::source_location &sourceLoc) {
    const std::string formattedLevel = FormatLogLevel(level);
    // prepend file:line, then append fmt
    std::cout << (std::format("{}:{}:{} | {}", formattedLevel,
                              sourceLoc.file_name(), sourceLoc.line(), message))
              << '\n';
  }
}  // namespace logzy
