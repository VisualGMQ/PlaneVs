if(NOT JsonCpp_FOUND AND PKG_CONFIG_FOUND)
    message(WARNING "cmake can't find jsoncpp, use pkg-config")
    pkg_check_modules(REQUIRED jsoncpp 
                      IMPORTED_TARGET GLOBAL)
    pkg_search_module(jsoncpp
                      REQUIRED jsoncpp
                      IMPORTED_TARGET GLOBAL)
    add_library(jsoncpp_static ALIAS PkgConfig::jsoncpp)
endif()
