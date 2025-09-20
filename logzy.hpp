#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <source_location>
#include <mutex>
#include <chrono>
#include <iomanip>

namespace logzy {

    // Log levels
    enum class LogLevel {
        DEBUG = 0,
        INFO = 1,
        WARN = 2,
        ERROR = 3,
        FATAL = 4
    };

    // Convert log level to string
    inline const char* to_string(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO:  return "INFO";
            case LogLevel::WARN:  return "WARN";
            case LogLevel::ERROR: return "ERROR";
            case LogLevel::FATAL: return "FATAL";
            default: return "UNKNOWN";
        }
    }

    class Logger {
    private:
        LogLevel min_level_ = LogLevel::INFO;
        std::mutex mutex_;

        // Get current timestamp as string
        std::string get_timestamp() const {
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch()) % 1000;
            
            std::stringstream ss;
            ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
            ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
            return ss.str();
        }

        // Extract just the filename from the full path
        std::string extract_filename(const std::string& path) const {
            size_t pos = path.find_last_of("/\\");
            return (pos == std::string::npos) ? path : path.substr(pos + 1);
        }

    public:
        // Set minimum log level
        void set_level(LogLevel level) {
            std::lock_guard<std::mutex> lock(mutex_);
            min_level_ = level;
        }

        // Get current log level
        LogLevel get_level() const {
            return min_level_;
        }

        // Check if level should be logged
        bool should_log(LogLevel level) const {
            return level >= min_level_;
        }

        // Main logging function
        template<typename... Args>
        void log(LogLevel level, 
                const std::source_location& location = std::source_location::current(),
                Args&&... args) {
            
            if (!should_log(level)) {
                return;
            }

            std::lock_guard<std::mutex> lock(mutex_);
            
            // Build the log message
            std::ostringstream oss;
            (oss << ... << args);
            
            // Format: [TIMESTAMP] [LEVEL] [file:line:function] message
            std::cout << "[" << get_timestamp() << "] "
                      << "[" << to_string(level) << "] "
                      << "[" << extract_filename(location.file_name()) 
                      << ":" << location.line() 
                      << ":" << location.function_name() << "] "
                      << oss.str() << std::endl;
        }

        // Convenience methods for different log levels
        template<typename... Args>
        void debug(Args&&... args) {
            log(LogLevel::DEBUG, std::source_location::current(), std::forward<Args>(args)...);
        }

        template<typename... Args>
        void info(Args&&... args) {
            log(LogLevel::INFO, std::source_location::current(), std::forward<Args>(args)...);
        }

        template<typename... Args>
        void warn(Args&&... args) {
            log(LogLevel::WARN, std::source_location::current(), std::forward<Args>(args)...);
        }

        template<typename... Args>
        void error(Args&&... args) {
            log(LogLevel::ERROR, std::source_location::current(), std::forward<Args>(args)...);
        }

        template<typename... Args>
        void fatal(Args&&... args) {
            log(LogLevel::FATAL, std::source_location::current(), std::forward<Args>(args)...);
        }

        // Internal log methods with explicit source location
        template<typename... Args>
        void debug_at(const std::source_location& location, Args&&... args) {
            log(LogLevel::DEBUG, location, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void info_at(const std::source_location& location, Args&&... args) {
            log(LogLevel::INFO, location, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void warn_at(const std::source_location& location, Args&&... args) {
            log(LogLevel::WARN, location, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void error_at(const std::source_location& location, Args&&... args) {
            log(LogLevel::ERROR, location, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void fatal_at(const std::source_location& location, Args&&... args) {
            log(LogLevel::FATAL, location, std::forward<Args>(args)...);
        }
    };

    // Global logger instance
    inline Logger& get_logger() {
        static Logger instance;
        return instance;
    }

    // Global convenience functions
    template<typename... Args>
    void debug(Args&&... args) {
        get_logger().debug(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(Args&&... args) {
        get_logger().info(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn(Args&&... args) {
        get_logger().warn(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(Args&&... args) {
        get_logger().error(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void fatal(Args&&... args) {
        get_logger().fatal(std::forward<Args>(args)...);
    }

    // Global convenience functions with explicit source location
    template<typename... Args>
    void debug_at(const std::source_location& location, Args&&... args) {
        get_logger().debug_at(location, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info_at(const std::source_location& location, Args&&... args) {
        get_logger().info_at(location, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn_at(const std::source_location& location, Args&&... args) {
        get_logger().warn_at(location, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error_at(const std::source_location& location, Args&&... args) {
        get_logger().error_at(location, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void fatal_at(const std::source_location& location, Args&&... args) {
        get_logger().fatal_at(location, std::forward<Args>(args)...);
    }

    // Set global log level
    inline void set_level(LogLevel level) {
        get_logger().set_level(level);
    }

    // Get global log level
    inline LogLevel get_level() {
        return get_logger().get_level();
    }

} // namespace logzy

// Convenience macros for easier usage with proper source location
#define LOGZY_DEBUG(...) logzy::debug_at(std::source_location::current(), __VA_ARGS__)
#define LOGZY_INFO(...)  logzy::info_at(std::source_location::current(), __VA_ARGS__)
#define LOGZY_WARN(...)  logzy::warn_at(std::source_location::current(), __VA_ARGS__)
#define LOGZY_ERROR(...) logzy::error_at(std::source_location::current(), __VA_ARGS__)
#define LOGZY_FATAL(...) logzy::fatal_at(std::source_location::current(), __VA_ARGS__)