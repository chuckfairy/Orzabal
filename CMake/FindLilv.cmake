# - Try to find Lilv
# Once done this will define
#
#  LILV_FOUND - system has Lilv
#  LILV_INCLUDE_DIRS - the Lilv include directory
#  LILV_LIBRARIES - Link these to use Lilv
#  LILV_DEFINITIONS - Compiler switches required for using Lilv
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

find_package(PkgConfig)

if (NOT LILV_INCLUDE_DIRS)

    find_path(LILV_INCLUDE_DIR
        NAMES lilv.h
        HINTS /usr/local/lib/ /usr/local/include
        )

    set(LILV_INCLUDE_DIRS
        ${LILV_INCLUDE_DIR}
        )

    message( "${LILV_INCLUDE_DIR}" )

    # show the LILV_INCLUDE_DIRS variables only in the advanced view
    mark_as_advanced(LILV_INCLUDE_DIRS)

endif (NOT LILV_INCLUDE_DIRS)

if (LILV_INCLUDE_DIRS)
    # in cache already
    set(LILV_FOUND TRUE)
endif (LILV_INCLUDE_DIRS)

# vim: tw=90 ts=8 sw=2 sts=2 et sta noai
