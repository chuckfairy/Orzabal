# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# find the location of Qt header files and libraries
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)


# later on, we'll use Qt Creator to build out our UI
# Qt Creator creates .ui files which will be preprocessed for us (that's what qt5_wrap_ui does)
# After preprocessing, a .h and .cpp file are produced for each .ui file
# we add the binary output directory as an include directory so that we can include the .h file later on
file(GLOB example_UIS MainWindow.ui)

file(GLOB common-ladspa ../common/LADSPA/*.cpp)

qt5_wrap_ui(example_UIS ${example_UIS} )

#links
include_directories(${CMAKE_CURRENT_BINARY_DIR} ../common  )


# tell CMake to compile every .cpp file in this directory and add it to an executable named `example`
file(
    GLOB
    example_SRC
    *.cpp
    widget/*.cpp
)

add_executable(example ${example_SRC} ${common-ladspa})

target_link_libraries( example
    dl
    gabrielo-common-lv2 gabrielo-common
    "/usr/local/lib/liblilv-0.so"
)

#target_link_libraries( example dl Qt5::Widget Qt5::Core )


#target_link_libraries(example gabrielo-common)

#target_link_libraries(example PUBLIC gabrielo-common qtwidget qtcore)

# this tells CMake where the header files and dynamic libraries are that we need
qt5_use_modules(example Widgets Core)
