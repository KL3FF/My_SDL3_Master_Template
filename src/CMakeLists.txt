
add_subdirectory(core)
add_subdirectory(handler)
add_subdirectory(instance)


add_executable(Executable main.cpp)



target_link_libraries(Executable PRIVATE BundleAssetsHandler)
target_link_libraries(Executable PRIVATE ConfigInfo)
# target_link_libraries(Executable PRIVATE JsonConfigHandler)
# target_link_libraries(Executable PRIVATE InstanceHandler)
target_link_libraries(Executable PRIVATE TextureHandler)
target_link_libraries(Executable PRIVATE WindowHandler)
# target_link_libraries(Executable PRIVATE BaseObject)
target_link_libraries(Executable PRIVATE SDL3::SDL3)
target_link_libraries(Executable PRIVATE SDL3_image::SDL3_image)
# target_link_libraries(Executable PRIVATE nlohmann_json::nlohmann_json)



