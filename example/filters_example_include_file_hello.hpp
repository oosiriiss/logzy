#pragma once

#include <logzy/logzy.hpp>
#include <source_location>

constexpr void includedFunc() {

  logzy::info("Calling func from included header in '{}'",
              std::source_location::current().file_name());
  logzy::trace("Included func trace.");
  logzy::debug("Included func debug. MyKeyword");
  logzy::info("Included func info");
  logzy::warn("Included func warn. MyKeyword");
  logzy::error("Included func error. M y K e y w o r d");
  logzy::critical("Included func critical.");

}
