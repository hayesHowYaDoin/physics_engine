function(build_python)
    message("Building Python bindings...")

    add_subdirectory(${CMAKE_SOURCE_DIR}/libs/pybind11)

    pybind11_add_module(physics_backend_python)
    add_library(physics::python ALIAS physics_backend_python)
    
    add_subdirectory(${CMAKE_SOURCE_DIR}/python)

    target_link_libraries(physics_backend_python
        PRIVATE
            physics_backend
    )

endfunction()
