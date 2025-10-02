
#include <filesystem>
#include <optional>
#include <string>
#include <variant>

#include "logzy/logzy.hpp"

struct SomeUnformattableStruct {
  int x;
  int y;
};

int main() {  // NOLINT(bugprone-exception-escape)
  const std::optional<int> withValue = std::optional(1);
  const std::optional<int> noValue = std::nullopt;

  logzy::info("This is std::optional with value: {}", withValue);
  logzy::info("This is std::optional without value: {}", noValue);

  using MyVariant = std::variant<int, bool, float>;

  MyVariant var = MyVariant(1);
  logzy::info("This is std::variant<int,bool,float> with int value: {}", var);
  var = MyVariant(false);
  logzy::info("This is std::variant<int,bool,float> with bool value: {}", var);
  var = MyVariant(1.0F);
  logzy::info("This is std::variant<int,bool,float> with float value: {}", var);

  using UnformattableVariant = std::variant<int, SomeUnformattableStruct>;
  [[maybe_unused]] const UnformattableVariant var2 = UnformattableVariant(0);

  // This will not compile
  // logzy::critical("Does pritning unformattable clas work {}", var2);

  auto path = std::filesystem::path("/this/is/some/path");

  logzy::info("path is: {}", path);

  const wchar_t* wide = L"Hello";
  logzy::info("Wide string: {}", wide);

  std::wstring widestr = L"Hello Wide string";
  logzy::warn("Wide string: {}", widestr);

  std::wstring_view widesv = L"Hello Wide string view";
  logzy::warn("Wide string view: {}", widesv);

  std::println("wide string view {}", widestr);

  logzy::info("Hello {}", std::string("Hello"));

  return 0;
}
