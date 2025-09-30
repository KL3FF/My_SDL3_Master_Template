# -------------- BundleAssetsHandler -------------- 

add_library(BundleAssetsHandler STATIC "BundleAssetsHandler.cpp")
target_link_libraries(BundleAssetsHandler PRIVATE WindowConfig)

# -------------- ConfigHandler -------------- 

add_library(ConfigHandler STATIC "ConfigHandler.cpp")
target_link_libraries(ConfigHandler PRIVATE AppInfo)


# -------------- InstanceHandler -------------- 
add_library(InstanceHandler STATIC "InstanceHandler.cpp")




# -------------- InstanceHandler -------------- 
add_library(TextureHandler STATIC "TextureHandler.cpp")




# -------------- InstanceHandler -------------- 
add_library(AppWindow STATIC "AppWindow.cpp")
target_link_libraries(AppWindow PRIVATE ConfigHandler)
target_link_libraries(AppWindow PRIVATE WindowConfig)


# -------------- InstanceHandler -------------- 
add_library(DrawHandler STATIC "DrawHandler.cpp")

