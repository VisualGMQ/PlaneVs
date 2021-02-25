function(GetFilenameFromUrl URL FILENAME)
    set(FILENAME_REGEX ".+/(.+)")
    string(REGEX MATCH ${FILENAME_REGEX} FUNC_FILENAME ${URL})
    string(REGEX REPLACE ${FILENAME_REGEX} "\\1" FUNC_FILENAME "${FUNC_FILENAME}")
    set(${FILENAME} ${FUNC_FILENAME} PARENT_SCOPE)
endfunction()

# detect if third packages were exists, if not exists, download and unzip it
# @params
# DIR           the unzipped dir, if not found, will check if ZIP_FILE exists and try to unzip it.Will be expanded as ${CMAKE_SOURCE_DIR}/external/${DIR}
# ZIP_FILE      the zip_file under external, if not exists, use URL to download.Will be expanded as ${CMAKE_SOURCE_DIR}/external/${ZIP_FILE}
# DOWNLOAD_URL  the download url
function(DetectAndDownload DIR ZIP_FILE DOWNLOAD_URL)
    GetFilenameFromUrl(${DOWNLOAD_URL} FILENAME)
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/external/${DIR})
        if (NOT EXISTS ${CMAKE_SOURCE_DIR}/external/${ZIP_FILE})
            message(WARNING "can't find ${FILENAME}, download it from ${DOWNLOAD_URL}")
            file(DOWNLOAD ${DOWNLOAD_URL} ${CMAKE_SOURCE_DIR}/external/${FILENAME})
        endif()
        message(STATUS "unzipping external/${FILENAME}...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} tar xf ${FILENAME}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external
            RESULT_VARIABLE TAR_RESULT)
        if (NOT "${TAR_RESULT}" EQUAL "0")
            message(FATAL_ERROR "tar command unzipped external/${FILENAME} failed, please unzip it to external/ by yourself")
        endif()
    endif()
endfunction()
