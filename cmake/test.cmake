function(build_test)
    message("${CMAKE_CURRENT_SOURCE_DIR}: Building tests...")

    # Suppress GTest warnings
    cmake_policy(SET CMP0003 NEW)
    cmake_policy(SET CMP0012 NEW)

    CPMAddPackage(
        NAME googletest
        GITHUB_REPOSITORY google/googletest
        VERSION 1.14.0
        OPTIONS
            "INSTALL_GTEST OFF"
            "gtest_force_shared_crt ON"
    )

    add_executable(test_physics_engine)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
    
    target_include_directories(test_physics_engine
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/test
    )
    
    target_link_libraries(test_physics_engine
        PUBLIC
            gtest
            gtest_main
        PRIVATE
            physics_engine
    )

    include(GoogleTest)
    gtest_discover_tests(test_physics_engine)
    
endfunction()
