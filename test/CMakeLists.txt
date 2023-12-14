find_package(GTest REQUIRED)

enable_testing()

add_executable(test_cpp_source_template
    example/test_example.cpp
)

target_link_libraries(test_cpp_source_template
    PUBLIC
        GTest::GTest
        GTest::Main
        template::example
)

include(GoogleTest)
gtest_discover_tests(test_cpp_source_template)
