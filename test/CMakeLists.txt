include_directories(${CMAKE_SOURCE_DIR}/include ${GLM_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS} ${GLEW_LIBRARY_DIRS})
link_libraries(${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

file(COPY ./test_resources DESTINATION ${CMAKE_BINARY_DIR}/test)
file(COPY ../shader DESTINATION ${CMAKE_BINARY_DIR}/test)

add_executable(LearnJsonCpp ./LearnJsonCpp.cpp)
add_executable(SpriteReader_Work ./SpritReader_Work.cpp ../src/engin/app.cpp  ../src/image_sheet/image_sheet.cpp ../src/engin/texture.cpp ../src/engin/gl_shader.cpp ../src/engin/gl_program.cpp)
add_executable(TextureRepo_Work ./TextureRepo_Work.cpp ../src/engin/app.cpp . ../src/image_sheet/image_sheet.cpp ../src/engin/texture.cpp ../src/engin/texture_repo.cpp ../src/engin/gl_shader.cpp ../src/engin/gl_program.cpp)
