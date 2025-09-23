#include <optional>
#include <variant>

#include "logzy/logzy.hpp"

struct SomeUnformattableStruct {
  int x;
  int y;
};

int main() { // NOLINT(bugprone-exception-escape)
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

  return 0;
}
