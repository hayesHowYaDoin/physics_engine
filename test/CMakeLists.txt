find_package(GTest REQUIRED)

enable_testing()

add_executable(test_physics_backend)

add_subdirectory(domain)
# add_subdirectory(usecases)
# add_subdirectory(adapters)
# add_subdirectory(infrastructure)

target_link_libraries(test_physics_backend
    PUBLIC
        GTest::GTest
        GTest::Main
        physics_backend
)

include(GoogleTest)
gtest_discover_tests(test_physics_backend)
