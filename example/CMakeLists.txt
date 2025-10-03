cmake_minimum_required(VERSION 3.14)

project(logzyExamples CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

if(PROJECT_IS_TOP_LEVEL)
  find_package(logzy REQUIRED)
endif()

add_custom_target(run-examples)

function(add_example NAME)
  add_executable("${NAME}" "${NAME}.cpp")
  target_link_libraries("${NAME}" PRIVATE logzy::logzy)
  target_compile_features("${NAME}" PRIVATE cxx_std_23)
   # target_link_libraries("${NAME}" PRIVATE rainbowcpp::rainbowcpp)
  add_custom_target("run_${NAME}" COMMAND "${NAME}" VERBATIM)
  add_dependencies("run_${NAME}" "${NAME}")
  add_dependencies(run-examples "run_${NAME}")
endfunction()

add_example(basic_logging_example)
add_example(formatters_example)
add_example(debug_log_disable)

add_folders(Example)
