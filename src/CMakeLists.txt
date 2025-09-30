# add_subdirectory(config)
add_subdirectory(core)
add_subdirectory(gui)
add_subdirectory(handler)
add_subdirectory(instance)
add_subdirectory(scenes)


add_executable(MAIN main.cpp)

target_link_libraries(MAIN PRIVATE BundleAssetsHandler)
target_link_libraries(MAIN PRIVATE AppInfo)
target_link_libraries(MAIN PRIVATE TextureHandler)
target_link_libraries(MAIN PRIVATE AppWindow)
target_link_libraries(MAIN PRIVATE SDL3::SDL3)
target_link_libraries(MAIN PRIVATE SDL3_image::SDL3_image)
target_link_libraries(MAIN PRIVATE InstanceHandler)
target_link_libraries(MAIN PRIVATE GuiHandler)
target_link_libraries(MAIN PRIVATE EventHandler)




