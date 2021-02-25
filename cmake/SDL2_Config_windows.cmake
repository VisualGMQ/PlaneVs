include(${CMAKE_SOURCE_DIR}/cmake/tool.cmake)

if (NOT SDL2_FOUND)
    message(STATUS "cmake can't find SDL2, download it")
    DetectAndDownload(SDL2-2.0.14 SDL2-devel-2.0.14-VC.zip https://www.libsdl.org/release/SDL2-devel-2.0.14-VC.zip)

    set(SDL2_FOUND)
    set(SDL2_PREFIX ${CMAKE_SOURCE_DIR}/external/SDL2-2.0.14)
    set(SDL2_INCLUDE_DIRS ${SDL2_PREFIX}/include)
    set(SDL2_LIBDIR ${SDL2_PREFIX}/lib/x64)
    set(SDL2_LIBRARIES "-lSDL2main -lSDL2")
    file(GLOB SDL2_DLLS ${SDL2_PREFIX}/lib/x64/*.dll)
    file(COPY ${SDL2_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

if (NOT SDL2_IMAGE_FOUND)
    message(STATUS "cmake can't find SDL2_image, download it")
    DetectAndDownload(SDL2_image-2.0.5 SDL2_image-devel-2.0.5-VC.zip https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip)

    set(SDL2_IMAGE_FOUND)
    set(SDL2_IMAGE_PREFIX ${CMAKE_SOURCE_DIR}/external/SDL2_image-2.0.5)
    set(SDL2_IMAGE_INCLUDE_DIRS ${SDL2_IMAGE_PREFIX}/include)
    set(SDL2_IMAGE_LIBDIR ${SDL2_IMAGE_PREFIX}/lib/x64)
    set(SDL2_IMAGE_LIBRARIES "-lSDL2_image")
    file(GLOB SDL2_IMAGE_DLLS ${SDL2_IMAGE_PREFIX}/lib/x64/*.dll)
    file(COPY ${SDL2_IMAGE_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

if (NOT SDL2_TTF_FOUND)
    message(STATUS "cmake can't find SDL2_ttf, download it")
    DetectAndDownload(SDL2_ttf-2.0.15 SDL2_ttf-devel-2.0.15-VC.zip https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-VC.zip)

    set(SDL2_TTF_FOUND)
    set(SDL2_TTF_PREFIX ${CMAKE_SOURCE_DIR}/external/SDL2_ttf-2.0.15)
    set(SDL2_TTF_INCLUDE_DIRS ${SDL2_TTF_PREFIX}/include)
    set(SDL2_TTF_LIBDIR ${SDL2_TTF_PREFIX}/lib/x64)
    set(SDL2_TTF_LIBRARIES "-lSDL2_ttf")
    file(GLOB SDL2_TTF_DLLS ${SDL2_TTF_PREFIX}/lib/x64/*.dll)
    file(COPY ${SDL2_TTF_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

if (NOT SDL2_MIXER_FOUND)
    message(STATUS "cmake can't find SDL2_mixer, download it")
    DetectAndDownload(SDL2_mixer-2.0.4 SDL2_mixer-devel-2.0.4-VC.zip https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.4-VC.zip)

    set(SDL2_MIXER_FOUND)
    set(SDL2_MIXER_PREFIX ${CMAKE_SOURCE_DIR}/external/SDL2_mixer-2.0.4)
    set(SDL2_MIXER_INCLUDE_DIRS ${SDL2_MIXER_PREFIX}/include)
    set(SDL2_MIXER_LIBDIR ${SDL2_MIXER_PREFIX}/lib/x64)
    set(SDL2_MIXER_LIBRARIES "-lSDL2_mixer")
    file(GLOB SDL2_MIXER_DLLS ${SDL2_MIXER_PREFIX}/lib/x64/*.dll)
    file(COPY ${SDL2_MIXER_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()