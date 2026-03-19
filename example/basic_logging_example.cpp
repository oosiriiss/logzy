#include "logzy/logzy.hpp"

int main() {  // NOLINT(bugprone-exception-escape)

  logzy::trace("This is Trace with id {}", 0);
  logzy::debug("This is Debug with id {}", 1);
  logzy::info("This is Info with id {}", 2);
  logzy::warn("This is Warn with id {}", 3);
  logzy::error("This is Error with id {}", 4);
  logzy::critical("This is Critical with id {}", 5);
  return 0;
}
