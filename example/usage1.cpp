#include "logzy/logzy.hpp"

int main() {
  logzy::Info("This is Info with id {}", 1);
  logzy::Warn("This is Warn with id {}", 2);
  logzy::Error("This is Error with id {}", 3);
  logzy::Debug("This is Debug with id {}", 4);
  logzy::Critical("This is Critical with id {}", 69);
  return 0;
}
