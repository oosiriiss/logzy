#include "logzy/logzy.hpp"

int main() {
  logzy::info("This is Info with id {}", 1);
  logzy::warn("This is Warn with id {}", 2);
  logzy::error("This is Error with id {}", 3);
  logzy::debug("This is Debug with id {}", 4);
  logzy::critical("This is Critical with id {}", 0);
  return 0;
}
