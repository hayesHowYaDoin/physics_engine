include(cmake/build_lib.cmake)
include(cmake/build_test.cmake)

cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(physics_backend VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(USE_CLANG "Use clang" OFF)

if(USE_CLANG)
    set(CMAKE_CXX_COMPILER /usr/bin/clang++-17)
    set(CMAKE_CXX_COMPILER_AR /usr/bin/llvm-ar-17)
    set(CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS /usr/bin/clang-scan-deps-10)
else()
    set(CMAKE_CXX_COMPILER /usr/bin/g++-13)
endif()

build_physics_backend()

# option(BUILD_TESTING "Build tests" OFF)

# if(BUILD_TESTING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt")
#     build_test()
# endif()