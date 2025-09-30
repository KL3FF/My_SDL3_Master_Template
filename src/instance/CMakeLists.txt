add_library(BasicObject STATIC "BasicObject.cpp")
target_link_libraries(BasicObject PRIVATE SDL3_image::SDL3_image)
target_link_libraries(BasicObject PRIVATE TextureHandler)
target_link_libraries(BasicObject PRIVATE DrawHandler)