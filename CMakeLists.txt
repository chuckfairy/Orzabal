# Jack cmake

project( orzabal-all CXX )

cmake_minimum_required( VERSION 2.7 )

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_C_STANDARD 11 )

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wno-return-type")
set(CMAKE_C_FLAGS "-std=c11 ${CMAKE_C_FLAGS}")


# RPATH
set( CMAKE_MACOSX_RPATH 1 )

set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )



# Main setup

project( orzabal )

set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/CMake" )

set( ORZA_DATA_PATH "${PROJECT_SOURCE_DIR}/data")


# Config

set( ORZABAL_VERSION "0.7.0" )
set( ORZABAL_RELEASE_NAME "Mad World" )

set( ORZABAL_ROOT_PATH "${PROJECT_SOURCE_DIR}" )

set( ORZABAL_SRC_PATH "${PROJECT_SOURCE_DIR}/src" )

set( ORZABAL_LIB_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/lib" )


# CMake Config type [Linux, Pi]
# Linux default

add_definitions(-DORZA_BUILD_TYPE=${ORZA_BUILD_TYPE})

if( ORZA_BUILD_TYPE STREQUAL "" )
	set( ORZA_BUILD_TYPE "Linux" )
endif()


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


# Lib src

add_subdirectory( lib-src/liborza )
add_subdirectory( lib-src/liborza-qt )


# Src

add_subdirectory( src/common )
add_subdirectory( src/cli )

if( ORZA_BUILD_TYPE STREQUAL "Pi" )
	add_subdirectory( src/pi )
	add_definitions( -DIS_PI )
endif()

add_subdirectory( src/qt )

#add_subdirectory( test )
