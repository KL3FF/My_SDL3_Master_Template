


add_subdirectory(core)
add_subdirectory(handler)
add_subdirectory(instance)

add_library(ConfigInfo INTERFACE)
target_include_directories(ConfigInfo INTERFACE "./")