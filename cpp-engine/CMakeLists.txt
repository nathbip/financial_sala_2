cmake_minimum_required(VERSION 3.14)
project(CppEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO_WORKSHOP: Enable compiler warnings (e.g., -Wall -Wextra) here to improve code quality.
add_compile_options(-Wall -Wextra -Wpedantic)
# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Library
add_library(engine_lib src/TransactionProcessor.cpp)
target_include_directories(engine_lib PUBLIC include)

# Executable
add_executable(engine src/main.cpp)
target_link_libraries(engine PRIVATE engine_lib)

# Tests
enable_testing()
add_executable(engine_tests tests/test_processor.cpp)
target_link_libraries(engine_tests PRIVATE engine_lib gtest_main)

include(GoogleTest)
gtest_discover_tests(engine_tests)