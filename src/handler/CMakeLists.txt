add_library(ConfigManager STATIC "ConfigManager.cpp")
target_link_libraries(ConfigManager PRIVATE ConfigInfo)
add_library(InstanceHandler STATIC "InstanceHandler.cpp")
add_library(WindowHandler STATIC "WindowHandler.cpp")
