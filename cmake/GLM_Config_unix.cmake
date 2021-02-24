if(NOT GLM_FOUND AND PKG_CONFIG_FOUND)
    message(WARNING "cmake can't find glm, use pkg-config")
    pkg_check_modules(REQUIRED glm
                      IMPORTED_TARGET GLOBAL)
    pkg_search_module(glm
                      REQUIRED glm
                      IMPORTED_TARGET GLOBAL)
    add_library(glm::glm ALIAS PkgConfig::glm)
endif()
