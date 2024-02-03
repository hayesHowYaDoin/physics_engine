add_subdirectory(euler)

target_sources(test_physics_backend
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/test_step.cpp
)
