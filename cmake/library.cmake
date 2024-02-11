function(build_physics_backend)
    message("Building physics_backend...")

    add_library(physics_backend INTERFACE)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/units)

    target_include_directories(physics_backend
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_libraries(physics_backend
        INTERFACE
            units::units)

endfunction()
