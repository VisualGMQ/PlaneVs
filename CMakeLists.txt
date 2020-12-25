cmake_minimum_required(VERSION 3.10)
project(PlaneFight)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
add_compile_options(-std=c++17)

aux_source_directory(src SRC)

find_package(PkgConfig QUIET)

find_package(SDL2 QUIET)
find_package(SDL2_image QUIET)
find_package(GLM QUIET)
# find_package(GLEW REQUIRED)

# 如果没有找到SDL2和GLEW，则尝试通过pkg-config来查找
if(NOT SDL2_FOUND)
    message(WARNING "cmake can't find SDL2 SDL2_image, use pkg-config")
    pkg_check_modules(REQUIRED SDL2 SDL2_image)
    pkg_search_module(SDL2 REQUIRED sdl2)
    pkg_search_module(SDL2_image REQUIRED sdl2_image)
endif(NOT SDL2_FOUND)

if(NOT GLEW_FOUND)
    message(WARNING "cmake can't find glew, use pkg-config")
    pkg_check_modules(REQUIRED GLEW)
    pkg_search_module(GLEW REQUIRED glew)
endif(NOT GLEW_FOUND)

if(NOT GLM_FOUND)
    message(WARNING "cmake can't find glm, use pkg-config")
    pkg_check_modules(REQUIRED GLM)
    pkg_search_module(GLM REQUIRED glm)
endif(NOT GLM_FOUND)

find_package(OpenGL REQUIRED)

include_directories(./include ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS} ${SDL2_image_LIBRARY_DIRS} ${OPENGL_LIBRARY_DIRS} ${GLEW_LIBRARY_DIRS})
link_libraries(${SDL2_LIBRARIES} ${SDL2_image_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
add_executable(PlaneFight ${SRC})
