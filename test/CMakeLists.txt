cmake_minimum_required(VERSION 3.14)

project(logzyTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(logzy REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(logzy_test source/logzy_test.cpp)
target_link_libraries(logzy_test PRIVATE logzy::logzy)
target_compile_features(logzy_test PRIVATE cxx_std_20)

# add_test(NAME logzy_test COMMAND logzy_test)

# ---- End-of-file commands ----

add_folders(Test)
