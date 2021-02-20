if (NOT GLM_FOUND)
    set(GLM_URL https://gitee.com/mirrors/glm.git)
    message(STATUS "checking glm...")
    FetchContent_Declare(
        glm
        GIT_REPOSITORY ${GLM_URL}
	    GIT_TAG        0.9.9.8
	SOURCE_DIR	${CMAKE_SOURCE_DIR}/external/glm
    )
    FetchContent_MakeAvailable(glm)
endif()
