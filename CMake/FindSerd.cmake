# Include from project library
#
# SERD_FOUND - system has serd
# SERD_INCLUDE_DIRS - the serd include directory
# SERD_INCLUDE_FILE - Build with these
#

find_package(PkgConfig)

if( NOT SERD_INCLUDE_DIRS )

    set(SERD_INCLUDE_DIRS
      "${ORZABAL_ROOT_PATH}/lib-src/serd/src"
      "${ORZABAL_ROOT_PATH}/lib-src/serd"
    )

    set(SERD_INCLUDE_FILES
        "${ORZABAL_ROOT_PATH}/lib-src/serd/src/*.c"
    )

    message( "${SERD_INCLUDE_DIR}" )

endif()


# in cache already
if( SERD_INCLUDE_DIRS )
    set( SERD_FOUND TRUE )
endif()
