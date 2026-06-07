#include <logzy/logzy.hpp>
#include <print>
#include <utility>

#include "filters_example_include_file_hello.hpp"
#include "logzy/filter.hpp"
#include "logzy/log_level.hpp"

/////////////////////////////////////////////////
/// If you want to enable the filter logs just
/// set the boolean to true
/////////////////////////////////////////////////
constexpr bool enableFilterMessages = false;
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

namespace {
  template <typename... Args>
  void filterLog(std::format_string<Args...> fmt, Args&&... args) {
    if constexpr (enableFilterMessages) {
      std::println(fmt, std::forward<Args>(args)...);
    }
  }

  struct MinInfoFilter : public logzy::LogFilter {
    auto filterLevel(logzy::LogLevel level) -> bool override {
      filterLog("[MinInfoFilter] Checking if level '{}' is at least Info.",
                logzy::internal::toString(level));

      bool passed = std::to_underlying(level) >=
                    std::to_underlying(logzy::LogLevel::Info);

      if (passed) {
        filterLog("[MinInfoFilter] Level '{}' passed filtering",
                  logzy::internal::toString(level));
      } else {
        filterLog("[MinInfoFilter] Level '{}' did not pass filtering",
                  logzy::internal::toString(level));
      }

      return passed;
    }
  };

  struct FileNameFilter : public logzy::LogFilter {
    auto filterFile(std::string_view fileName) -> bool override {
      std::string_view searched = "hello";
      filterLog("[FileNameFilter]Checking if fileName '{}' contains '{}'",
                fileName, searched);

      bool contains = fileName.contains(searched);
      if (contains) {
        filterLog("[FileNameFilter] Yes! '{}' does contain '{}'", fileName,
                  searched);

      } else {
        filterLog("[FileNameFilter] No. '{}' does not contain '{}'", fileName,
                  searched);
      }

      return contains;
    }
  };

  struct MessageFilter : public logzy::LogFilter {
    auto filterMessage(std::string_view message) -> bool override {
      std::string_view searched = "MyKeyword";
      filterLog("[MessageFilter] Checking if message '{}' contains '{}'",
                message, searched);

      bool contains = message.contains(searched);
      if (contains) {
        filterLog("[MessageFilter] Yes! '{}' does contain '{}'", message,
                  searched);

      } else {
        filterLog("[MessageFilter] No. '{}' does not contain '{}'", message,
                  searched);
      }

      return contains;
    }
  };

  struct CombinedFilter : MinInfoFilter, FileNameFilter, MessageFilter {};

  void divider(std::string_view title) {
    std::println(
        "\n=====================================================\n{}\n========="
        "===="
        "========================================\n",
        title);
  }
}  // namespace

auto main() -> int {
  std::println(
      "Filtering logs based on log level.\nAttempting to send logs of each "
      "level. Logs >= Info should be printed");
  logzy::getLogger().filter = std::make_unique<MinInfoFilter>();
  logzy::trace("Hello this is trace message, it shouldn't be printed");
  logzy::debug("Hello this is debug message, it shouldn't be printed");
  logzy::info("Hello this is info message, it shouldn be printed");
  logzy::warn("Hello this is warn message, it shouldn be printed");
  logzy::error("Hello this is error message, it shouldn be printed");
  logzy::critical("Hello this is critical message, it shouldn be printed");

  divider(
      "Filtering by file name. Logs from this file shouldn't be printed. But "
      "inclded file should.");
  logzy::getLogger().filter = std::make_unique<FileNameFilter>();
  logzy::info("This is a function from current file, it shouldn't be printed");
  includedFunc();

  divider(
      "Filtering by message's content. Messages containing 'MyKeyword' should "
      "be printed and others should not.");
  logzy::getLogger().filter = std::make_unique<MessageFilter>();
  logzy::info("MyKeyword Hello! I should be printed");
  logzy::error("My Keyword Hello! I should not be printed");

  divider(
      "LogLevels >= Info\n Only from file that contains 'hello' in file name\n"
      "Only messages that contain 'MyKeyword' in the content");
  std::println("Combining the filters into one filter");
  logzy::trace("Hello this is trace message, it shouldn't be printed");
  logzy::debug("Hello this is debug message, it shouldn't be printed");
  logzy::info("Hello this is info message, it shouldn be printed");
  logzy::warn("Hello this is warn message, it shouldn be printed");
  logzy::error("Hello this is error message, it shouldn be printed");
  logzy::critical("Hello this is critical message, it shouldn be printed");
  includedFunc();
}
