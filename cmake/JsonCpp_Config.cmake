find_package(JsonCpp QUIET)

if (CMAKE_SYSTEM_NAME MATCHES Windows)
    include(${CMAKE_SOURCE_DIR}/cmake/JsonCpp_Config_windows.cmake)
else()
    include(${CMAKE_SOURCE_DIR}/cmake/JsonCpp_Config_unix.cmake)
endif()