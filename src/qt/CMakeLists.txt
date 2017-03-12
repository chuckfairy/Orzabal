# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set( AUTOGEN_TARGET_DEPENDS ON )

# find the location of Qt header files and libraries
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Qml REQUIRED)


file(GLOB orzabal.qt_UIS MainWindow.ui)
file(GLOB common-ladspa ../common/LADSPA/*.cpp)

qt5_wrap_ui(orzabal.qt_UIS ${orzabal.qt_UIS} )

#list(APPEND QML_DIRS "Styles")
#set(QML_IMPORT_PATH "${QML_DIRS}" CACHE STRING "Qt Creator extra qml import paths")

qt5_add_resources(RESOURCES ./Resources.qrc)


#links
include_directories(${CMAKE_CURRENT_BINARY_DIR} ../common )


# tell CMake to compile every .cpp file in this directory and add it to an executable named `orzabal.qt`
file(
    GLOB
    orzabal.qt_SRC
    MainWindow.cpp
    main.cpp
    ui_MainWindow.h
    widget/*.cpp
    Settings/*.cpp
    Settings/Events/*.cpp
)

add_executable(orzabal.qt ${orzabal.qt_SRC} ${common-ladspa} ${RESOURCES})

target_link_libraries( orzabal.qt
    dl
    orzabal-common-lv2 orzabal-common
    orzabal-common-jack
    "/usr/local/lib/liblilv-0.so"
    Qt5::Widgets Qt5::Core
    Qt5::Qml
)
