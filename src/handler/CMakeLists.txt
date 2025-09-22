add_library(JsonConfigHandler STATIC "JsonConfigHandler.cpp")
target_link_libraries(JsonConfigHandler PRIVATE ConfigInfo)
add_library(InstanceHandler STATIC "InstanceHandler.cpp")


add_library(TextureHandler STATIC "TextureHandler.cpp")

add_library(WindowHandler STATIC "WindowHandler.cpp")
target_link_libraries(WindowHandler PRIVATE JsonConfigHandler)

