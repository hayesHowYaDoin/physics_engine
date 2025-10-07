function(build_benchmark)
    message("${CMAKE_CURRENT_SOURCE_DIR}: Building benchmarks...")

    # Suppress benchmark warnings
    cmake_policy(SET CMP0003 NEW)
    cmake_policy(SET CMP0012 NEW)

    CPMAddPackage(
        NAME benchmark
        GITHUB_REPOSITORY google/benchmark
        VERSION 1.8.3
        OPTIONS
            "BENCHMARK_ENABLE_TESTING OFF"
            "BENCHMARK_ENABLE_INSTALL OFF"
            "BENCHMARK_ENABLE_GTEST_TESTS OFF"
    )

    add_executable(benchmark_physics_engine)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/benchmark)
    
    target_include_directories(benchmark_physics_engine
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/benchmark
    )
    
    target_link_libraries(benchmark_physics_engine
        PUBLIC
            benchmark::benchmark
            benchmark::benchmark_main
        PRIVATE
            physics_engine
    )
    
endfunction()