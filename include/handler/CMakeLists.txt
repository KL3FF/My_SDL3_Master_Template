target_include_directories(ConfigManager PUBLIC "./")
target_link_libraries(ConfigManager PRIVATE ConfigInfo)
target_link_libraries(ConfigManager PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(InstanceHandler PUBLIC "./")
target_link_libraries(InstanceHandler PRIVATE BaseObject)

target_include_directories(WindowHandler PUBLIC "./")

target_link_libraries(WindowHandler PRIVATE SDL3::SDL3)
target_link_libraries(WindowHandler PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(WindowHandler PRIVATE ConfigManager)