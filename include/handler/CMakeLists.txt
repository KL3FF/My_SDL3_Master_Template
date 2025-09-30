# -------------- BundleAssetsHandler -------------- 

target_include_directories(BundleAssetsHandler PUBLIC "./")


# -------------- ConfigHandler -------------- 

target_include_directories(ConfigHandler PUBLIC "./")



# -------------- InstanceHandler -------------- 
target_include_directories(InstanceHandler PUBLIC "./")
target_link_libraries(InstanceHandler PUBLIC BasicObject)



# -------------- InstanceHandler -------------- 
target_include_directories(TextureHandler PUBLIC "./")
target_link_libraries(TextureHandler PRIVATE SDL3::SDL3)
target_link_libraries(TextureHandler PRIVATE SDL3_image::SDL3_image)
target_link_libraries(TextureHandler PRIVATE WindowConfig)

# -------------- InstanceHandler -------------- 
target_include_directories(AppWindow PUBLIC "./")
target_link_libraries(AppWindow PRIVATE SDL3::SDL3)



# -------------- InstanceHandler -------------- 
target_include_directories(DrawHandler PUBLIC "./")