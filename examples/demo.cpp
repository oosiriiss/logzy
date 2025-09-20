#include "../logzy.hpp"
#include <string>

void demonstrate_basic_logging() {
    logzy::info("This is an info message");
    logzy::warn("This is a warning message");
    logzy::error("This is an error message");
    logzy::debug("This debug message won't show by default");
}

void demonstrate_with_variables() {
    int value = 42;
    std::string name = "logzy";
    
    logzy::info("Integer value: ", value);
    logzy::info("String value: ", name);
    logzy::info("Mixed values: name=", name, ", value=", value);
}

void demonstrate_log_levels() {
    logzy::info("Current log level: ", static_cast<int>(logzy::get_level()));
    
    // Set to DEBUG level to see debug messages
    logzy::set_level(logzy::LogLevel::DEBUG);
    logzy::info("Changed log level to DEBUG");
    
    logzy::debug("Now you can see debug messages!");
    logzy::info("Info message");
    logzy::warn("Warning message");
    logzy::error("Error message");
    
    // Set back to INFO level
    logzy::set_level(logzy::LogLevel::INFO);
    logzy::info("Set log level back to INFO");
    logzy::debug("This debug message won't show");
}

void demonstrate_macros() {
    LOGZY_INFO("Using macro for info");
    LOGZY_WARN("Using macro for warning");
    LOGZY_ERROR("Using macro for error");
}

void some_function() {
    logzy::info("Called from some_function()");
}

int main() {
    logzy::info("=== logzy C++ Logging Library Demo ===");
    
    logzy::info("1. Basic logging:");
    demonstrate_basic_logging();
    
    logzy::info("\n2. Logging with variables:");
    demonstrate_with_variables();
    
    logzy::info("\n3. Different log levels:");
    demonstrate_log_levels();
    
    logzy::info("\n4. Using macros:");
    demonstrate_macros();
    
    logzy::info("\n5. Source location tracking:");
    some_function();
    
    logzy::info("\n=== Demo complete ===");
    
    return 0;
}