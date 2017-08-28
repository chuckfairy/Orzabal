# Include from project library
#
# LILV_FOUND - system has Lilv
# LILV_INCLUDE_DIRS - the Lilv include directory
# LILV_INCLUDE_FILE - Build with these
#

find_package(PkgConfig)

if( NOT LILV_INCLUDE_DIRS )

    set(LILV_INCLUDE_DIRS
      "${ORZABAL_ROOT_PATH}/lib-src/lilv/src"
      "${ORZABAL_ROOT_PATH}/lib-src/lilv"
    )

    set(LILV_INCLUDE_FILES
      "${ORZABAL_ROOT_PATH}/lib-src/lilv/src/*.c"
      "${ORZABAL_ROOT_PATH}/lib-src/lilv/src/zix/*.c"
    )

    message( "${LILV_INCLUDE_DIR}" )

    # show the LILV_INCLUDE_DIRS variables only in the advanced view
    mark_as_advanced(LILV_INCLUDE_DIRS)

endif()


# in cache already
if( LILV_INCLUDE_DIRS )
    set( LILV_FOUND TRUE )
endif()
