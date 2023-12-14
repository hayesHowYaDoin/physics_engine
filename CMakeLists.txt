cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API aa1f7df0-828a-4fcd-9afc-2dc80491aca7)

project(cpp_source_template)

if(NOT "${CMAKE_GENERATOR}" STREQUAL "Ninja Multi-Config")
    message(WARNING "It's recommended to use -G \"Ninja Multi-Config\" for this project (using: ${CMAKE_GENERATOR}).")
    # OR, if you want to force-stop the configuration:
    # message(FATAL_ERROR "Please use -G \"Ninja Multi-Config\" for this project.")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")
set(CMAKE_MAKE_PROGRAM ninja)

option(USE_CLANG "Use clang" OFF)

if(USE_CLANG)
    set(CMAKE_CXX_COMPILER clang++-17)
    set(CMAKE_CXX_COMPILER_AR llvm-ar-17)
    set(CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS usr/bin/clang-scan-deps-10)
else()
    set(CMAKE_CXX_COMPILER g++-13)
endif()

add_subdirectory(src)

add_library(template::example ALIAS cpp_source_template)
target_include_directories(cpp_source_template 
    PUBLIC 
        include
    PRIVATE
        src
)

option(BUILD_TESTING "Build tests" ON)

if(BUILD_TESTING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt")
    add_subdirectory(test)
endif()