function(build_physics_backend)
    # Add your custom logic here
    message("Building physics_backend...")

    add_library(physics_backend STATIC)

    add_subdirectory(${CMAKE_SOURCE_DIR}/src)

    target_include_directories(physics_backend 
        PUBLIC 
            ${CMAKE_SOURCE_DIR}/include
        PRIVATE
            ${CMAKE_SOURCE_DIR}/src
    )    
endfunction()
