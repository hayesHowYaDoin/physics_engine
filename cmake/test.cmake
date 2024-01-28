function(build_test)
    message("${CMAKE_CURRENT_SOURCE_DIR}: Building tests...")

    # Suppress GTest warnings
    cmake_policy(SET CMP0003 NEW)
    cmake_policy(SET CMP0012 NEW)

    find_package(GTest REQUIRED)
    enable_testing()

    add_executable(test_physics_backend)

    add_subdirectory(${CMAKE_SOURCE_DIR}/test)
    
    target_link_libraries(test_physics_backend
        PUBLIC
            GTest::GTest
            GTest::Main
        PRIVATE
            physics_backend
    )
    
    #get_target_property (private_include_dirs physics_backend INCLUDE_DIRECTORIES)
    #target_include_directories (test_physics_backend PRIVATE ${private_include_dirs})

    include(GoogleTest)
    gtest_discover_tests(test_physics_backend)
    
endfunction()
