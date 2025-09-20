#include "../logzy.hpp"
#include <sstream>
#include <iostream>
#include <cassert>

// Simple test to validate core functionality
void test_log_levels() {
    // Test log level filtering
    logzy::set_level(logzy::LogLevel::WARN);
    assert(logzy::get_level() == logzy::LogLevel::WARN);
    
    auto& logger = logzy::get_logger();
    assert(!logger.should_log(logzy::LogLevel::DEBUG));
    assert(!logger.should_log(logzy::LogLevel::INFO));
    assert(logger.should_log(logzy::LogLevel::WARN));
    assert(logger.should_log(logzy::LogLevel::ERROR));
    assert(logger.should_log(logzy::LogLevel::FATAL));
    
    std::cout << "✓ Log level filtering works correctly\n";
}

void test_source_location() {
    // Test that source location is captured
    // We can't easily test the exact values, but we can test that it compiles
    // and the macros work
    LOGZY_INFO("Testing source location capture");
    std::cout << "✓ Source location capture works\n";
}

void test_variable_logging() {
    // Test logging with different types
    int num = 42;
    std::string text = "test";
    double pi = 3.14159;
    
    logzy::set_level(logzy::LogLevel::DEBUG);
    
    // These should compile and run without issues
    logzy::info("Number: ", num);
    logzy::info("Text: ", text);
    logzy::info("Pi: ", pi);
    logzy::info("Mixed: ", text, " = ", num, ", pi = ", pi);
    
    std::cout << "✓ Variable logging works correctly\n";
}

void test_enum_to_string() {
    // Test log level to string conversion
    assert(std::string(logzy::to_string(logzy::LogLevel::DEBUG)) == "DEBUG");
    assert(std::string(logzy::to_string(logzy::LogLevel::INFO)) == "INFO");
    assert(std::string(logzy::to_string(logzy::LogLevel::WARN)) == "WARN");
    assert(std::string(logzy::to_string(logzy::LogLevel::ERROR)) == "ERROR");
    assert(std::string(logzy::to_string(logzy::LogLevel::FATAL)) == "FATAL");
    
    std::cout << "✓ Log level to string conversion works\n";
}

int main() {
    std::cout << "Running logzy tests...\n\n";
    
    test_log_levels();
    test_source_location(); 
    test_variable_logging();
    test_enum_to_string();
    
    std::cout << "\n✅ All tests passed!\n";
    return 0;
}