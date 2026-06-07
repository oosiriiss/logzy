cmake_minimum_required(VERSION 3.14)

project(logzyExamples CXX)

include(../cmake/project-is-top-level.cmake)

if(PROJECT_IS_TOP_LEVEL)
  find_package(logzy REQUIRED)
endif()


function(add_example NAME)
  add_executable("${NAME}" "${NAME}.cpp")
  target_link_libraries("${NAME}" PRIVATE logzy::logzy)
  target_compile_features("${NAME}" PRIVATE cxx_std_23)
  # target_link_libraries("${NAME}" PRIVATE rainbowcpp::rainbowcpp)
endfunction()

add_example(general_example)
add_example(formatters_example)
add_example(compile_time_min_log_level)
add_example(filters)
