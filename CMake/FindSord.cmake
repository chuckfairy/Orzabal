# Include from project library
#
# SORD_FOUND - system has sord
# SORD_INCLUDE_DIRS - the sord include directory
# SORD_INCLUDE_FILE - Build with these
#

find_package(PkgConfig)

if( NOT SORD_INCLUDE_DIRS )

    set(SORD_INCLUDE_DIRS
      "${ORZABAL_ROOT_PATH}/lib-src/sord/src"
      "${ORZABAL_ROOT_PATH}/lib-src/sord"
      "${ORZABAL_ROOT_PATH}/lib-src/sord/sord"
    )

    set(SORD_INCLUDE_FILES
      "${ORZABAL_ROOT_PATH}/lib-src/sord/src/*.c"
      "${ORZABAL_ROOT_PATH}/lib-src/sord/src/zix/*.c"
    )

    message( "${SORD_INCLUDE_DIR}" )

endif()


# in cache already
if( SORD_INCLUDE_DIRS )
    set( SORD_FOUND TRUE )
endif()
