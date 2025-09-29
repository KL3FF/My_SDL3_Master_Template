add_library(WindowConfig INTERFACE)
target_include_directories(WindowConfig INTERFACE "./")
target_link_libraries(WindowConfig INTERFACE nlohmann_json::nlohmann_json)
target_link_libraries(WindowConfig INTERFACE ConfigHandler)



add_library(AppInfo INTERFACE)
target_include_directories(AppInfo INTERFACE "./")
