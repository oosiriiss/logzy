#pragma once

#include <cstdint>
#include <string_view>
#include <utility>

namespace logzy {

  enum class LogLevel : std::uint8_t {
    Trace = 0,
    Debug = 1,
    Info = 2,
    Warning = 3,
    Error = 4,
    Critical = 5
  };

  namespace internal {

    constexpr LogLevel
        COMP_MIN_LOG_LEVEL =  //  NOLINT(readability-identifier-naming)
#if defined(LOGZY_MIN_TRACE)
        LogLevel::Trace;
#elif defined(LOGZY_MIN_DEBUG)
        LogLevel::Debug;
#elif defined(LOGZY_MIN_INFO)
        LogLevel::Info;
#elif defined(LOGZY_MIN_WARNING)
        LogLevel::Warning;
#elif defined(LOGZY_MIN_ERROR)
        LogLevel::Error;
#elif defined(LOGZY_MIN_CRITICAL)
        LogLevel::Critical;
#else
#define LOGZY_MIN_DEBUG
        LogLevel::Trace;
#endif

    constexpr std::string_view toString(const LogLevel level) {
      switch (level) {
        case LogLevel::Trace:
          return "TRACE";
        case LogLevel::Debug:
          return "DEBUG";
        case LogLevel::Info:
          return "INFO";
        case LogLevel::Warning:
          return "WARNING";
        case LogLevel::Error:
          return "ERROR";
        case LogLevel::Critical:
          return "CRITICAL";
      }
      std::unreachable();
    }
  }  // namespace internal
}  // namespace logzy
