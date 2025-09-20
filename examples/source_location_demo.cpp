#include "../logzy.hpp"
#include <string>

void function_demo() {
    // Using function calls - will show logzy.hpp locations
    logzy::info("Function call: This shows template location");
    
    // Using macros - will show actual source locations  
    LOGZY_INFO("Macro call: This shows actual source location");
}

int main() {
    logzy::info("=== Source Location Comparison ===");
    
    // Direct function calls
    logzy::info("Direct function call from main");
    logzy::warn("Direct warning from main");
    logzy::error("Direct error from main");
    
    // Macro calls
    LOGZY_INFO("Macro call from main");
    LOGZY_WARN("Macro warning from main");
    LOGZY_ERROR("Macro error from main");
    
    // From another function
    function_demo();
    
    return 0;
}