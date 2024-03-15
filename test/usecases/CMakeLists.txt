target_sources(test_physics_backend
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/test_constrain.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test_collision.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test_polygon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test_simulation.cpp
)
