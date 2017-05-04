# Jack cmake

project(orzabal-all CXX)

cmake_minimum_required( VERSION 2.7 )

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_C_STANDARD 11 )

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

INCLUDE( CPack )

project(orzabal)

set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/CMake" )

set( ORZABAL_ROOT_PATH "${PROJECT_SOURCE_DIR}" )

set( ORZABAL_LIB_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/lib" )

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()


## Main includes

add_subdirectory( src/common )

add_subdirectory( src/common/Audio )

add_subdirectory( src/common/LADSPA )

add_subdirectory( src/common/Jack )

add_subdirectory( src/common/LV2 )

add_subdirectory( src/qt )

#add_subdirectory( src/include/jalv )

add_subdirectory( test )
