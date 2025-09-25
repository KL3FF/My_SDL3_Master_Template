add_library(BundleAssetsHandler STATIC "BundleAssetsHandler.cpp")
target_link_libraries(BundleAssetsHandler PRIVATE ConfigInfo)


add_library(JsonConfigHandler STATIC "JsonConfigHandler.cpp")
target_link_libraries(JsonConfigHandler PRIVATE ConfigInfo)

add_library(InstanceHandler STATIC "InstanceHandler.cpp")

add_library(TextureHandler STATIC "TextureHandler.cpp")
target_link_libraries(TextureHandler PRIVATE SDL3_image::SDL3_image)
target_link_libraries(TextureHandler PRIVATE BundleAssetsHandler)
target_link_libraries(TextureHandler PRIVATE AppWindow)

add_library(AppWindow STATIC "AppWindow.cpp")
target_link_libraries(AppWindow PRIVATE JsonConfigHandler)

