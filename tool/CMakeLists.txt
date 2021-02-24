add_executable(SpriteSheet_Unpacker "")

target_sources(SpriteSheet_Unpacker PUBLIC ${CMAKE_SOURCE_DIR}/tool/spritesheet_unpacker.cpp)

target_include_directories(SpriteSheet_Unpacker PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_link_directories(SpriteSheet_Unpacker PUBLIC ${SDL2_LIBDIR} ${SDL2_IMAGE_LIBDIR} ${SDL2_TTF_LIBDIR})
target_link_libraries(SpriteSheet_Unpacker PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} glm::glm jsoncpp_static)

target_compile_features(SpriteSheet_Unpacker PUBLIC cxx_std_17 c_std_11)
