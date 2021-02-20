include(FindPkgConfig)

# if cmake not found SDL, use pkg-config
if (PKG_CONFIG_FOUND)
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
endif()