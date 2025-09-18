
add_subdirectory(core)
add_subdirectory(handler)
add_subdirectory(instance)


add_executable(Executable main.cpp)
# target_include_directories(Executable PRIVATE ${CMAKE_SOURCE_DIR}/include/config)
target_link_libraries(Executable PRIVATE ConfigInfo)
target_link_libraries(Executable PRIVATE ConfigManager)
target_link_libraries(Executable PRIVATE InstanceHandler)
target_link_libraries(Executable PRIVATE WindowHandler)
target_link_libraries(Executable PRIVATE BaseObject)
target_link_libraries(Executable PRIVATE SDL3::SDL3)
# target_link_libraries(Executable PRIVATE nlohmann_json::nlohmann_json)


