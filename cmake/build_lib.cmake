function(build_physics_backend)
    message("Building physics_backend...")

    add_library(physics_backend STATIC)

    add_subdirectory(${CMAKE_SOURCE_DIR}/src)
    add_subdirectory(${CMAKE_SOURCE_DIR}/libs)

    target_include_directories(physics_backend 
        PUBLIC 
            ${CMAKE_SOURCE_DIR}/include
        PRIVATE
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/libs
    )    
endfunction()
