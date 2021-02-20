if (NOT EXISTS ${CMAKE_SOURCE_DIR}/external/SDL_FontCache)
    set(FONTCACHE_URL https://github.com/grimfang4/SDL_FontCache.git)
    find_program(GIT_EXECUTABLE git)
    if (NOT GIT_EXECUTABLE)
        message(FATAL_ERROR "you must have git to fetch SDL_FontCache.Or you can download it to external/ dir by yourself from ${FONTCACHE_URL}")
    else()
        message(STATUS "can't find FontCache, fetch it from ${FONTCACHE_URL} ...")
        execute_process(
            COMMAND ${GIT_EXECUTABLE} clone ${FONTCACHE_URL}
            WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}/external
            TIMEOUT             300
            RESULT_VARIABLE     FONTCACHE_RESULT)
        if(NOT "${FONTCACHE_RESULT}" EQUAL "0")
            if(FONTCACHE_RESULT EQUAL "timeout")
                message(STATUS "fetch SDL_FontCache timeout, please check your network status and retry")
            else()
                message(FATAL_ERROR "fetch SDL_FontCache failed")
                file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/external/SDL_FontCache)
            endif()
        endif()
    endif()
endif()

set(SDL_FONTCACHE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/SDL_FontCache)
set(SDL_FONTCACHE_SOURCE ${CMAKE_SOURCE_DIR}/external/SDL_FontCache/SDL_FontCache.c)
