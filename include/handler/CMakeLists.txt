
target_include_directories(InstanceHandler PUBLIC "./")
target_link_libraries(InstanceHandler  PRIVATE BaseObject)

target_include_directories(WindowHandler PUBLIC "./")
target_link_libraries(WindowHandler PRIVATE SDL3::SDL3)