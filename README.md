# logzy

A modern C++ header-only logging micro-library with automatic source location tracking using C++20's `std::source_location`.

## Features

- **Header-only**: Just include `logzy.hpp` and you're ready to go
- **C++20 `std::source_location`**: Automatic capture of file, line, and function information
- **Multiple log levels**: DEBUG, INFO, WARN, ERROR, FATAL
- **Thread-safe**: Built-in mutex protection for concurrent logging
- **Easy to use**: Simple function calls or convenient macros
- **Configurable**: Adjustable log level filtering
- **Timestamp support**: Millisecond precision timestamps
- **Lightweight**: Minimal overhead and dependencies

## Requirements

- C++20 compatible compiler (GCC 13+, Clang 12+, MSVC 2022+)
- Standard library with `<source_location>` support

## Quick Start

```cpp
#include "logzy.hpp"

int main() {
    // Basic logging
    logzy::info("Hello, world!");
    logzy::warn("This is a warning");
    logzy::error("This is an error");
    
    // Logging with variables
    int value = 42;
    logzy::info("The answer is: ", value);
    
    // Using macros for better source location
    LOGZY_INFO("This shows exact source location");
    LOGZY_ERROR("Error with precise location info");
    
    return 0;
}
```

## Usage

### Basic Logging

```cpp
#include "logzy.hpp"

// Different log levels
logzy::debug("Debug message");    // Only shown if level is DEBUG
logzy::info("Info message");      // Default minimum level
logzy::warn("Warning message");
logzy::error("Error message");
logzy::fatal("Fatal message");
```

### Logging with Variables

```cpp
std::string name = "logzy";
int version = 1;

logzy::info("Library: ", name, ", Version: ", version);
logzy::error("Failed to process ", count, " items");
```

### Log Level Control

```cpp
// Set minimum log level
logzy::set_level(logzy::LogLevel::DEBUG);  // Show all messages
logzy::set_level(logzy::LogLevel::WARN);   // Only WARN, ERROR, FATAL

// Check current level
auto level = logzy::get_level();
```

### Macros for Better Source Location

For the most accurate source location information, use the provided macros:

```cpp
LOGZY_DEBUG("Debug info");
LOGZY_INFO("Information");
LOGZY_WARN("Warning");
LOGZY_ERROR("Error occurred");
LOGZY_FATAL("Fatal error");
```

**Note**: Function calls show the template location within `logzy.hpp`, while macros capture the exact location in your source code.

### Advanced Usage

```cpp
// Using the logger instance directly
auto& logger = logzy::get_logger();
logger.set_level(logzy::LogLevel::DEBUG);
logger.info("Direct logger usage");

// Check if a level will be logged
if (logger.should_log(logzy::LogLevel::DEBUG)) {
    // Expensive debug computation
    std::string debug_info = compute_debug_info();
    logger.debug("Debug info: ", debug_info);
}
```

## Output Format

The logging output format is:
```
[TIMESTAMP] [LEVEL] [file:line:function] message
```

Example:
```
[2025-09-20 18:46:43.826] [INFO] [main.cpp:15:int main()] Hello, world!
[2025-09-20 18:46:43.826] [WARN] [utils.cpp:42:void process_data()] Invalid data detected
```

## Compilation

Compile with C++20 support:

```bash
g++ -std=c++20 -o your_program your_program.cpp
clang++ -std=c++20 -o your_program your_program.cpp
```

## Thread Safety

logzy is thread-safe. All logging operations are protected by an internal mutex, ensuring safe concurrent access from multiple threads.

## Log Levels

| Level | Value | Description |
|-------|--------|-------------|
| DEBUG | 0 | Detailed information for debugging |
| INFO  | 1 | General information (default level) |
| WARN  | 2 | Warning messages |
| ERROR | 3 | Error conditions |
| FATAL | 4 | Fatal errors |

## Examples

See the `examples/` directory for complete usage examples:
- `demo.cpp` - Comprehensive feature demonstration
- `source_location_demo.cpp` - Source location tracking comparison

To build and run examples:
```bash
g++ -std=c++20 -o examples/demo examples/demo.cpp
./examples/demo
```

## License

This project is open source. See the repository for license details.

## Contributing

Contributions are welcome! Please feel free to submit issues and pull requests.
