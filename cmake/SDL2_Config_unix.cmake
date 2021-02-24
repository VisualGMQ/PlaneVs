# if cmake not found SDL, use pkg-config
if (PKG_CONFIG_FOUND)
    if(NOT SDL2_FOUND)
        message(WARNING "cmake can't find SDL2, use pkg-config")
        pkg_check_modules(REQUIRED SDL2 )
        pkg_search_module(SDL2 REQUIRED sdl2)
        if (NOT SDL2_LIBDIR)
            set(SDL2_LIBDIR ${SDL2_LIBRARY_DIRS})
        endif()
    endif()

    if(NOT SDL2_IMAGE_FOUND)
        message(WARNING "cmake can't find SDL2_image, use pkg-config")
        pkg_check_modules(REQUIRED SDL2_image )
        pkg_search_module(SDL2_IMAGE REQUIRED sdl2_image)
        if (NOT SDL2_IMAGE_LIBDIR)
            set(SDL2_IMAGE_LIBDIR ${SDL2_IMAGE_LIBRARY_DIRS})
        endif()
    endif()

    if(NOT SDL2_TTF_FOUND)
        message(WARNING "cmake can't find SDL2_ttf, use pkg-config")
        pkg_check_modules(REQUIRED SDL2_ttf)
        pkg_search_module(SDL2_TTF REQUIRED sdl2_ttf)
        if (NOT SDL2_TTF_LIBDIR)
            set(SDL2_TTF_LIBDIR ${SDL2_TTF_LIBRARY_DIRS})
        endif()
    endif()

    if(NOT SDL2_MIXER_FOUND)
        message(WARNING "cmake can't find SDL2_mixer, use pkg-config")
        pkg_check_modules(REQUIRED SDL2_mixer)
        pkg_search_module(SDL2_MIXER REQUIRED sdl2_mixer)
        if (NOT SDL2_MIXER_LIBDIR)
            set(SDL2_MIXER_LIBDIR ${SDL2_MIXER_LIBRARY_DIRS})
        endif()
    endif()
endif()
