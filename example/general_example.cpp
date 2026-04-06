#include <optional>
#include <variant>
#include "logzy/logzy.hpp"

int main() {  

  logzy::trace("Starting up");
  logzy::debug("x = {}", 42);
  logzy::info("Server listening on port {}", 8080);
  logzy::warn("Config not found, using defaults");
  logzy::error("Some optional is: {} and the other one is: {}",
               std::optional<int>({15}), std::optional<int>{});
  logzy::critical("Critical value of: {}",
                  std::variant<int, long, float>(0.23F));
}
