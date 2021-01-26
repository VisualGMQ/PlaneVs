include_directories(${CMAKE_SOURCE_DIR}/include ${GLM_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS} ${GLEW_LIBRARY_DIRS})
link_libraries(${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

file(COPY ./test_resources DESTINATION ${CMAKE_BINARY_DIR}/test)
file(COPY ../shader DESTINATION ${CMAKE_BINARY_DIR}/test)

set(TEST_SRC ${SRC})
list(TRANSFORM TEST_SRC PREPEND ../)
add_executable(SpriteReader_Work ./SpriteReader_Work.cpp ${TEST_SRC})
add_executable(TextureRepo_Work ./TextureRepo_Work.cpp ${TEST_SRC})
add_executable(Sprite_Work ./Sprite_Work.cpp ${TEST_SRC})
add_executable(SpriteSheetCache_Work ./SpriteSheetCache_Work.cpp ${TEST_SRC})
