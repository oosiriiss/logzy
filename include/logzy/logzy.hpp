#pragma once

#include <concepts>
#include <cstdint>
#include <print>
#include <source_location>
#include <string>
#include <type_traits>
#include <utility>

#include "logzy/formatters.hpp"
#include "logzy/log_level.hpp"
#include "logzy/logger.hpp"
#include "rainbowcpp/colors.hpp"
#include "rainbowcpp/rainbowcpp.hpp"

namespace logzy {
  namespace internal {

    inline Logger
        g_logger;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

  }  // namespace internal

#define FORWARD_GLOBAL_LOGGER_METHOD(/*NOLINT(cppcoreguidelines-macro-usage)*/ \
                                     GLOBAL_METHOD_NAME, LOGGER_METHOD_NAME)   \
  template <typename... Args>                                                  \
  constexpr void GLOBAL_METHOD_NAME(log_format<Args...> format,                \
                                    Args &&...args) {                          \
    internal::g_logger.LOGGER_METHOD_NAME<Args...>(                            \
        format, std::forward<Args>(args)...);                                  \
  }

  FORWARD_GLOBAL_LOGGER_METHOD(trace, trace);
  FORWARD_GLOBAL_LOGGER_METHOD(debug, debug);
  FORWARD_GLOBAL_LOGGER_METHOD(info, info);
  FORWARD_GLOBAL_LOGGER_METHOD(warn, warn);
  FORWARD_GLOBAL_LOGGER_METHOD(error, error);
  FORWARD_GLOBAL_LOGGER_METHOD(critical, critical);
}  // namespace logzy
