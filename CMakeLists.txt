# Jack cmake

cmake_minimum_required( VERSION 2.7 )

set( CMAKE_CXX_STANDARD 11 )

project(gabrielo)

set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/CMake" )

set( GABRIELO_ROOT_PATH "${PROJECT_SOURCE_DIR}" )

set( GABRIELO_LIB_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/lib" )

add_subdirectory( src )

add_subdirectory( src/gui )

add_subdirectory( src/qt )
