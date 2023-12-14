find_package(GTest REQUIRED)

enable_testing()

add_executable(test_cpp_source_template)

add_subdirectory(domain)
# add_subdirectory(usecases)
# add_subdirectory(adapters)
# add_subdirectory(infrastructure)

target_link_libraries(test_cpp_source_template
    PUBLIC
        GTest::GTest
        GTest::Main
        template::example
)

include(GoogleTest)
gtest_discover_tests(test_cpp_source_template)
