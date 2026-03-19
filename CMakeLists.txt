cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    logzy
    VERSION 0.1.0
    DESCRIPTION "C++ Logging utilities"
    HOMEPAGE_URL " "
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)


include(FetchContent)
FetchContent_Declare(
   rainbowcpp
   GIT_REPOSITORY https://github.com/oosiriiss/rainbowcpp
   GIT_TAG 0.3
)
FetchContent_MakeAvailable(rainbowcpp)

add_library(
    logzy_logzy
    source/logzy.cpp
    include/logzy/formatters.hpp
    include/logzy/logzy.hpp
)
add_library(logzy::logzy ALIAS logzy_logzy)
target_link_libraries(logzy_logzy PUBLIC rainbowcpp::rainbowcpp)


# G++ 15.2.0 requiresthis for std::__write_to_terminal
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_libraries(logzy_logzy PRIVATE stdc++exp)
endif()

include(GenerateExportHeader)
generate_export_header(
    logzy_logzy
    BASE_NAME logzy
    EXPORT_FILE_NAME export/logzy/logzy_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(logzy_logzy PUBLIC LOGZY_STATIC_DEFINE)
endif()

set_target_properties(
    logzy_logzy PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME logzy
    OUTPUT_NAME logzy
)

target_include_directories(
    logzy_logzy ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    logzy_logzy SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(logzy_logzy PUBLIC cxx_std_23)


# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${logzy_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Developer mode ----

if(NOT logzy_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of logzy"
  )
endif()

include(cmake/dev-mode.cmake)
