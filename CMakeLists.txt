cmake_minimum_required(VERSION 3.10)
project(PlaneFight)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Og -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(TOOL ON)
    set(TEST ON)
endif()

find_package(PkgConfig QUIET)

find_package(SDL2 QUIET)
find_package(SDL2_image QUIET)
find_package(SDL2_ttf QUIET)
find_package(SDL2_mixer QUIET)
find_package(JsonCpp QUIET)

# 如果没有找到SDL2和GLEW，则尝试通过pkg-config来查找
if(NOT SDL2_FOUND)
    message(WARNING "cmake can't find SDL2, use pkg-config")
    pkg_check_modules(REQUIRED SDL2 )
    pkg_search_module(SDL2 REQUIRED sdl2)
endif()

if(NOT SDL2_IMAGE_FOUND)
    message(WARNING "cmake can't find SDL2_image, use pkg-config")
    pkg_check_modules(REQUIRED SDL2_image )
    pkg_search_module(SDL2_image REQUIRED sdl2_image)
endif()

if(NOT SDL2_TTF_FOUND)
    message(WARNING "cmake can't find SDL2_ttf, use pkg-config")
    pkg_check_modules(REQUIRED SDL2_ttf)
    pkg_search_module(SDL2_ttf REQUIRED sdl2_ttf)
endif()

if(NOT SDL2_MIXER_FOUND)
    message(WARNING "cmake can't find SDL2_mixer, use pkg-config")
    pkg_check_modules(REQUIRED SDL2_mixer)
    pkg_search_module(SDL2_mixer REQUIRED sdl2_mixer)
endif()

if(NOT JsonCpp_FOUND)
    message(WARNING "cmake can't find jsoncpp, use pkg-config")
    pkg_check_modules(REQUIRED JsonCpp)
    pkg_search_module(JSONCPP REQUIRED jsoncpp)
endif()

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_mixer_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS} ${JSONCPP_INCLUDE_DIRS} ./external)
link_directories(${SDL2_LIBRARY_DIRS} ${SDL2_mixer_LIBRARY_DIRS} ${SDL2_image_LIBRARY_DIRS} ${SDL2_ttf_LIBRARY_DIRS} ${JSONCPP_LIBRARY_DIRS})
link_libraries(${SDL2_LIBRARIES} ${SDL2_mixer_LIBRARIES} ${SDL2_image_LIBRARIES} ${SDL2_ttf_LIBRARIES} ${JSONCPP_LIBRARIES})

aux_source_directory(src/base SRC)
aux_source_directory(src/engin SRC)
aux_source_directory(src/engin/input SRC)
aux_source_directory(src/engin/ui SRC)
aux_source_directory(src/game SRC)
aux_source_directory(src/game/controller SRC)
aux_source_directory(src/image_sheet SRC)
aux_source_directory(external SRC)

set(GAME_EXE_NAME ${CMAKE_PROJECT_NAME})
add_executable(${GAME_EXE_NAME} ${SRC} src/main.cpp)

target_include_directories(${GAME_EXE_NAME} PRIVATE ./include)

file(COPY resources DESTINATION ${PROJECT_BINARY_DIR})

# macro for add test
macro(MADD_TEST test_name)
    add_test(NAME ${test_name}
             COMMAND ${test_name}
             WORKING_DIRECTORY test)
endmacro()

# Enable Compile Tests for PlaneVS
if(DEFINED TEST)
    add_subdirectory(test)
    enable_testing()
    MADD_TEST(SpriteReader_Work)
    MADD_TEST(TextureRepo_Work)
    MADD_TEST(Sprite_Work)
    MADD_TEST(SpriteSheetCache_Work)
    MADD_TEST(Animation_Work)
    MADD_TEST(Texture_Work)
    MADD_TEST(Music_Work)
    MADD_TEST(MusicRepo_Work)
    MADD_TEST(Font_Work)
    MADD_TEST(Text_Work)
    MADD_TEST(UI_Work)
endif()

if (DEFINED TOOL)
    add_subdirectory(tool)
endif()
