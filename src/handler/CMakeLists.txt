add_library(BundleAssetsHandler STATIC "BundleAssetsHandler.cpp")
target_link_libraries(BundleAssetsHandler PRIVATE ConfigInfo)


add_library(JsonConfigHandler STATIC "JsonConfigHandler.cpp")
target_link_libraries(JsonConfigHandler PRIVATE ConfigInfo)
add_library(InstanceHandler STATIC "InstanceHandler.cpp")


add_library(TextureHandler STATIC "TextureHandler.cpp")
target_link_libraries(TextureHandler PRIVATE SDL3_image::SDL3_image)
target_link_libraries(TextureHandler PRIVATE BundleAssetsHandler)


add_library(WindowHandler STATIC "WindowHandler.cpp")
target_link_libraries(WindowHandler PRIVATE JsonConfigHandler)

