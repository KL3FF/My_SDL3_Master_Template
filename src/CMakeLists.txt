
add_subdirectory(core)
add_subdirectory(handler)
add_subdirectory(instance)

add_executable(MAIN main.cpp)

target_link_libraries(MAIN PRIVATE BundleAssetsHandler)
target_link_libraries(MAIN PRIVATE ConfigInfo)
target_link_libraries(MAIN PRIVATE TextureHandler)
target_link_libraries(MAIN PRIVATE WindowHandler)
target_link_libraries(MAIN PRIVATE SDL3::SDL3)
target_link_libraries(MAIN PRIVATE SDL3_image::SDL3_image)


# target_link_libraries(MAIN PRIVATE nlohmann_json::nlohmann_json)
# target_link_libraries(MAIN PRIVATE BaseObject)
# target_link_libraries(MAIN PRIVATE JsonConfigHandler)
# target_link_libraries(MAIN PRIVATE InstanceHandler)
