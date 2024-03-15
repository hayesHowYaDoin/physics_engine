function(build_physics_engine)
    message("Building physics_engine...")

    add_library(physics_engine INTERFACE)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/units)

    target_include_directories(physics_engine
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_libraries(physics_engine
        INTERFACE
            units::units)

endfunction()
