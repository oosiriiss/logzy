cmake_minimum_required(VERSION 3.14)


project(
    logzy
    VERSION 0.2.7
    DESCRIPTION "C++ Logging utilities"
    HOMEPAGE_URL ""
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)


include(FetchContent)
FetchContent_Declare(
   rainbowcpp
   GIT_REPOSITORY https://github.com/oosiriiss/rainbowcpp
   GIT_TAG 0.3
)

FetchContent_MakeAvailable(rainbowcpp)

add_library(
    logzy_logzy
    INTERFACE
    include/logzy/formatters.hpp
    include/logzy/logzy.hpp
)
add_library(logzy::logzy ALIAS logzy_logzy)
target_link_libraries(logzy_logzy INTERFACE rainbowcpp::rainbowcpp)


# G++ 15.2.0 requiresthis for std::__write_to_terminal
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
   target_link_libraries(logzy_logzy INTERFACE stdc++exp)
endif()


set_property(
    TARGET logzy_logzy PROPERTY
    EXPORT_NAME logzy
)

target_include_directories(
    logzy_logzy ${warning_guard}
    INTERFACE
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(logzy_logzy INTERFACE cxx_std_23)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
   option(BUILD_EXAMPLES "Build examples tree." ON)
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()
