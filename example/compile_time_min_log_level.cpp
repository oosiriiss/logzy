

// One of these can be set as a preprocessor definiton to make all logging
// functions below specified logging level noops
//
// LOGZY_MIN_TRACE (Default)
// LOGZY_MIN_DEBUG
// LOGZY_MIN_INFO
// LOGZY_MIN_WARNING
// LOGZY_MIN_ERROR
// LOGZY_MIN_CRITICAL

#define LOGZY_MIN_WARNING
#include "logzy/logzy.hpp"

auto main() -> int {
  logzy::trace("Example logzy::trace! This should not print");
  logzy::debug("Example logzy::debug! This should not print");
  logzy::info("Example logzy::info! This should not print");
  logzy::warn("Example logzy::warn! This should print");
  logzy::error("Example logzy::error! This should print");
  logzy::critical("Example logzy::critical! This should print");
  return 0;
}
