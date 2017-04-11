# Include from project library
#
# SRATOM_FOUND - system has sratom
# SRATOM_INCLUDE_DIRS - the sratom include directory
# SRATOM_INCLUDE_FILE - Build with these
#

find_package(PkgConfig)

if( NOT SRATOM_INCLUDE_DIRS )

    set(SRATOM_INCLUDE_DIRS
      "${ORZABAL_ROOT_PATH}/lib-src/sratom"
    )

    set(SRATOM_INCLUDE_FILES
      "${ORZABAL_ROOT_PATH}/lib-src/sratom/src/*.c"
    )

    message( "${SRATOM_INCLUDE_DIR}" )

endif()


# in cache already
if( SRATOM_INCLUDE_DIRS )
    set( SRATOM_FOUND TRUE )
endif()
