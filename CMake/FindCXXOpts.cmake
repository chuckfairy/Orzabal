# Include from project library
#
# CXXOPTS_FOUND - system has cxxopts
# CXXOPTS_INCLUDE_DIRS - the cxxopts include directory
# CXXOPTS_INCLUDE_FILE - Build with these
#

find_package(PkgConfig)

if( NOT CXXOPTS_INCLUDE_DIRS )

    set(CXXOPTS_INCLUDE_DIRS
      "${ORZABAL_ROOT_PATH}/lib-src/cxxopts"
    )

    set(CXXOPTS_INCLUDE_FILES
        "${ORZABAL_ROOT_PATH}/lib-src/cxxopts/*.c"
    )

    message( "${CXXOPTS_INCLUDE_DIR}" )

endif()


# in cache already
if( CXXOPTS_INCLUDE_DIRS )
    set( CXXOPTS_FOUND TRUE )
endif()
