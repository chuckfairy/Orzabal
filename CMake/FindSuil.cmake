# Include from project library
#
# SUIL_FOUND - system has suil
# SUIL_INCLUDE_DIRS - the suil include directory
# SUIL_INCLUDE_FILE - Build with these
#

find_package(PkgConfig)

if( NOT SUIL_INCLUDE_DIRS )

    set(SUIL_INCLUDE_DIRS
      "${ORZABAL_ROOT_PATH}/lib-src/suil/src"
      "${ORZABAL_ROOT_PATH}/lib-src/suil"
      "/usr/include/gtk-2.0"
    )

    set(SUIL_INCLUDE_FILES
      "${ORZABAL_ROOT_PATH}/lib-src/suil/src/host.c"
      "${ORZABAL_ROOT_PATH}/lib-src/suil/src/instance.c"
      "${ORZABAL_ROOT_PATH}/lib-src/suil/src/x11_in_qt5.cpp"
    )

    message( "${SUIL_INCLUDE_DIR}" )

endif()


# in cache already
if( SUIL_INCLUDE_DIRS )
    set( SUIL_FOUND TRUE )
endif()
