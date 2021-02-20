if (NOT JsonCpp_FOUND)
    set(JSONCPP_URL https://gitee.com/mirrors/jsoncpp.git)
    message(STATUS "checking jsoncpp...")
    FetchContent_Declare(
        jsoncpp
        GIT_REPOSITORY ${JSONCPP_URL}
        GIT_TAG        1.9.4
	SOURCE_DIR	${CMAKE_SOURCE_DIR}/external/jsoncpp
    )
    FetchContent_MakeAvailable(jsoncpp)
endif()
