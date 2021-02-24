cmake_minimum_required(VERSION 3.14...3.18)
project(PlaneFight
	VERSION 0.0.1
	LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(TOOL "compile tools" OFF)
option(TEST "compile tests" OFF)
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(TOOL ON)
    set(TEST ON)
else()
    set(TOOL OFF)
    set(TEST OFF)
endif()

# config externals
include(FetchContent)
if (NOT CMAKE_SYSTEM_NAME MATCHES Windows)
    include(FindPkgConfig)
endif()
include(${CMAKE_SOURCE_DIR}/cmake/GLM_Config.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/JsonCpp_Config.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/SDL2_Config.cmake)

set(SDL_DEP_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
set(SDL_DEP_LIBDIR ${SDL2_LIBDIR} ${SDL2_IMAGE_LIBDIR} ${SDL2_MIXER_LIBDIR} ${SDL2_TTF_LIBDIR})
set(SDL_DEP_LIBRARIES ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# compile every parts of engin
aux_source_directory(src/base ENGIN_BASE_SRC)
aux_source_directory(src/image_sheet ENGIN_BASE_SRC)
add_library(GameEngin_base STATIC "")
target_sources(GameEngin_base PRIVATE ${ENGIN_BASE_SRC})
target_include_directories(GameEngin_base PUBLIC ${SDL_DEP_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
target_link_directories(GameEngin_base PUBLIC ${SDL_DEP_LIBDIR})
target_link_libraries(GameEngin_base PUBLIC ${SDL_DEP_LIBRARIES} glm::glm jsoncpp_static)
target_compile_features(GameEngin_base PUBLIC cxx_std_17 c_std_11)

aux_source_directory(src/engin ENGIN_ENGIN_SRC)
aux_source_directory(src/engin/input ENGIN_ENGIN_SRC)
aux_source_directory(src/engin/ui ENGIN_ENGIN_SRC)
add_library(GameEngin_engin STATIC "")
target_sources(GameEngin_engin PRIVATE ${ENGIN_ENGIN_SRC})
target_link_libraries(GameEngin_engin PUBLIC GameEngin_base)

# compile game
aux_source_directory(src/game GAME_SRC)
aux_source_directory(src/game/controller GAME_SRC)

set(GAME_EXE_NAME ${CMAKE_PROJECT_NAME})
add_executable(${GAME_EXE_NAME} "")
target_sources(${GAME_EXE_NAME}
		PUBLIC ${GAME_SRC}
		PRIVATE ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${GAME_EXE_NAME} PUBLIC GameEngin_engin)

file(COPY resources DESTINATION ${PROJECT_BINARY_DIR})

if(TEST)
    add_subdirectory(test)
endif()

if(TOOL)
    add_subdirectory(tool)
endif()
