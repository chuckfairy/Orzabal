# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(AUTOGEN_TARGET_DEPENDS ON)

# find the location of Qt header files and libraries
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Qml REQUIRED)


file(GLOB orzabal.qt_UIS
    MainWindow.ui
    Pi/PiTab.ui
    widget/PatchBay.ui
    widget/PatchBayItem.ui
)

file(GLOB common-ladspa ../common/LADSPA/*.cpp)

qt5_wrap_ui(orzabal.qt_UIS ${orzabal.qt_UIS} )

#list(APPEND QML_DIRS "Styles")
#set(QML_IMPORT_PATH "${QML_DIRS}" CACHE STRING "Qt Creator extra qml import paths")

qt5_add_resources(RESOURCES ./Resources.qrc)


#links

FIND_PACKAGE(Boost)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ../common /usr/local/lib
    "${ORZABAL_ROOT_PATH}/lib-src"
    "${ORZABAL_ROOT_PATH}/lib-src/lilv"
    "${ORZABAL_ROOT_PATH}/lib-src/sratom"
    "${ORZABAL_ROOT_PATH}/lib-src/sord"
    "${ORZABAL_ROOT_PATH}/lib-src/suil"
    "${ORZABAL_ROOT_PATH}/lib-src/serd"

    "${ORZABAL_ROOT_PATH}/src"
    "${ORZABAL_ROOT_PATH}/src/common/Audio"

    ${Boost_INCLUDE_DIR}
)


# tell CMake to compile every .cpp file in this directory and add it to an executable named `orzabal.qt`
file(
    GLOB
    orzabal.qt_SRC
    Pi/*.cpp
    MainWindow.cpp
    main.cpp
    **/moc_*.cpp
    *.moc
    ui_MainWindow.h
    widget/*.cpp
    LV2/*.cpp
    Layouts/*.cpp
    Settings/*.cpp
    Settings/Events/*.cpp
)


QT5_WRAP_CPP( ${orzabal.qt_SRC} )


# CMake Config type
# Pi for fullscreen
# Linux default

add_definitions(-DORZA_BUILD_TYPE=${ORZA_BUILD_TYPE})

if( ORZA_BUILD_TYPE STREQUAL "Pi" )
    set( ORZABAL_QT_BUILD_TYPE "Pi" )
else()
    set( ORZABAL_QT_BUILD_TYPE "Linux" )
endif()

configure_file(Config/BuildType.h.in Config/BuildType.h)


# Main executable

add_executable(orzabal.qt ${orzabal.qt_SRC} ${common-ladspa} ${RESOURCES})

find_package( Boost 1.45.0 COMPONENTS filesystem regex )

target_link_libraries( orzabal.qt
    PUBLIC
    dl
    orzabal-common
    orzabal-common-jack
    orzabal-common-plugin
    orzabal-cli
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Boost::regex
)

install( TARGETS
   orzabal.qt

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)

#Desktop file
if (UNIX)
	install(FILES orzabal.qt.desktop DESTINATION /usr/local/share/applications)
	install(FILES ../assets/orzabal.png
		DESTINATION /usr/local/share/icons)
endif()
