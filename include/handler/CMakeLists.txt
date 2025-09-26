target_include_directories(BundleAssetsHandler PUBLIC "./")

target_include_directories(JsonConfigHandler PUBLIC "./")
target_link_libraries(JsonConfigHandler PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(InstanceHandler PUBLIC "./")
target_link_libraries(InstanceHandler PRIVATE BaseObject)



target_include_directories(TextureHandler PUBLIC "./")
target_link_libraries(TextureHandler PRIVATE SDL3::SDL3)
target_link_libraries(TextureHandler PRIVATE SDL3_image::SDL3_image)
target_link_libraries(TextureHandler PRIVATE WindowConfig)

target_include_directories(AppWindow PUBLIC "./")
target_link_libraries(AppWindow PRIVATE SDL3::SDL3)
# target_link_libraries(AppWindow PRIVATE nlohmann_json::nlohmann_json)

