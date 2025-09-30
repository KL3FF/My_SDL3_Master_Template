# -------------- BundleAssetsHandler -------------- 

add_library(BundleAssetsHandler STATIC "BundleAssetsHandler.cpp")
target_link_libraries(BundleAssetsHandler PRIVATE WindowConfig)

# -------------- ConfigHandler -------------- 

add_library(ConfigHandler STATIC "ConfigHandler.cpp")
target_link_libraries(ConfigHandler PRIVATE AppInfo)


# -------------- InstanceHandler -------------- 
add_library(InstanceHandler STATIC "InstanceHandler.cpp")
target_link_libraries(InstanceHandler PRIVATE SDL3_image::SDL3_image)



# -------------- GuiHandler -------------- 
add_library(GuiHandler STATIC "GuiHandler.cpp")
target_link_libraries(GuiHandler PRIVATE SDL3_image::SDL3_image)



# -------------- TextureHandler -------------- 
add_library(TextureHandler STATIC "TextureHandler.cpp")




# -------------- AppWindow -------------- 
add_library(AppWindow STATIC "AppWindow.cpp")
target_link_libraries(AppWindow PRIVATE ConfigHandler)
target_link_libraries(AppWindow PRIVATE WindowConfig)


# -------------- DrawHandler -------------- 
add_library(DrawHandler STATIC "DrawHandler.cpp")