# Jack cmake

project( orzabal-all CXX )

cmake_minimum_required( VERSION 2.7 )

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_C_STANDARD 11 )

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")


# RPATH
set( CMAKE_MACOSX_RPATH 1 )

set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )


# CPack

INCLUDE( CPack )


# Main setup

project( orzabal )

set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/CMake" )


# Config

set( ORZABAL_VERSION "0.6.1" )

set( ORZABAL_ROOT_PATH "${PROJECT_SOURCE_DIR}" )

set( ORZABAL_SRC_PATH "${PROJECT_SOURCE_DIR}/src" )

set( ORZABAL_LIB_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/lib" )

# @TODO add possible OS check

set( ORZABAL_HAS_LV2 true )

set( ORZABAL_PLUGIN_TYPES
    "LV2"
    "Test"
)


# Boost

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()


## Main includes

add_subdirectory( src/common )

add_subdirectory( src/common/Midi )

add_subdirectory( src/common/Audio )

add_subdirectory( src/common/LADSPA )

add_subdirectory( src/common/Jack )

add_subdirectory( src/common/LV2 )

add_subdirectory( src/common/PluginSearch )

add_subdirectory( src/cli )

add_subdirectory( src/qt )

add_subdirectory( test )
