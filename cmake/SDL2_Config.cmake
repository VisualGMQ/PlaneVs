find_package(SDL2 QUIET)
find_package(SDL2_image QUIET)
find_package(SDL2_mixer QUIET)
find_package(SDL2_ttf QUIET)

if (CMAKE_SYSTEM_NAME MATCHES Windows)
    include(${CMAKE_SOURCE_DIR}/cmake/SDL2_Config_windows.cmake)
else()
    include(${CMAKE_SOURCE_DIR}/cmake/SDL2_Config_unix.cmake)
endif()