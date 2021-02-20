find_package(GLM QUIET)

if (CMAKE_SYSTEM_NAME MATCHES Windows)
    include(${CMAKE_SOURCE_DIR}/cmake/GLM_Config_windows.cmake)
else()
    include(${CMAKE_SOURCE_DIR}/cmake/GLM_Config_unix.cmake)
endif()