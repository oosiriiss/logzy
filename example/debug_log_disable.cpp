#include "logzy/logzy.hpp"

auto main() -> int {
  logzy::info(
      "If you have set the cmake flag 'DISABLE_BUILD_LOGS' to 'ON' or defined "
      "LOGZY_DISABLE_DEBUG_LOGS before including the library you shouldn't see "
      "the following debug messages.");

  logzy::debug("Debug 1");
  logzy::debug("Debug 2");
  logzy::debug("Debug 3");
  logzy::debug("Debug 4");

  logzy::info("Example end :)");

  return 0;
}
