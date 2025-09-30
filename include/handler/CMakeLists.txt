# -------------- BundleAssetsHandler -------------- 

target_include_directories(BundleAssetsHandler PUBLIC "./")


# -------------- ConfigHandler -------------- 

target_include_directories(ConfigHandler PUBLIC "./")



# -------------- InstanceHandler -------------- 
target_include_directories(InstanceHandler PUBLIC "./")
target_link_libraries(InstanceHandler PUBLIC BasicObject)
target_link_libraries(InstanceHandler PRIVATE SDL3_image::SDL3_image)


# -------------- GuiHandler-------------- 
target_include_directories(GuiHandler PUBLIC "./")
target_link_libraries(GuiHandler PUBLIC BasicGui)
target_link_libraries(GuiHandler PRIVATE SDL3_image::SDL3_image)


# -------------- TextureHandler -------------- 
target_include_directories(TextureHandler PUBLIC "./")
target_link_libraries(TextureHandler PRIVATE SDL3::SDL3)
target_link_libraries(TextureHandler PRIVATE SDL3_image::SDL3_image)
target_link_libraries(TextureHandler PUBLIC WindowConfig)

# -------------- AppWindow -------------- 
target_include_directories(AppWindow PUBLIC "./")
target_link_libraries(AppWindow PRIVATE SDL3::SDL3)



# -------------- DrawHandler -------------- 
target_include_directories(DrawHandler PUBLIC "./")