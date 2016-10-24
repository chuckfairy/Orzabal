# Jack cmake

cmake_minimum_required( VERSION 2.7 )

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/CMake")

add_subdirectory( src )

add_subdirectory( src/qt )
