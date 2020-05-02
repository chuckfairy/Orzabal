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
	Widget/PatchBay.ui
	Widget/PatchBayItem.ui
	LV2/PluginArea.ui
	MidiControl/Control.ui
	MidiControl/ControlPort.ui
	MidiControl/ControlPortValue.ui
)

qt5_wrap_ui(orzabal.qt_UIS ${orzabal.qt_UIS} )

qt5_add_resources(RESOURCES ./Resources.qrc)


#links

#FIND_PACKAGE(Boost)
find_package( Boost 1.45.0 COMPONENTS filesystem regex )

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

	"${ORZABAL_ROOT_PATH}/lib-src/liborza/src"
	"${ORZABAL_ROOT_PATH}/lib-src/liborza/lib-src"
	"${ORZABAL_ROOT_PATH}/lib-src/liborza-qt/src"
	"${ORZABAL_ROOT_PATH}/lib-src/liborza-qt/lib-src"

	"${CMAKE_CURRENT_BINARY_DIR}/../../lib-src/liborza/src"
	"${CMAKE_CURRENT_BINARY_DIR}/../../lib-src/liborza-qt/src"

	${Boost_INCLUDE_DIR}
)


# tell CMake to compile every .cpp file in this directory and add it to an executable named `orzabal.qt`
file(
	GLOB
	orzabal.qt_SRC
	"${ORZABAL_ROOT_PATH}/lib-src/QtAwesome/*.cpp"
	${orzabal.qt_UIS}
	MainWindow.cpp
	main.cpp
	#**/moc_*.cpp
	#*.moc
	ui_MainWindow.h
	Widget/*.cpp
	LV2/*.cpp
	Layouts/**/*.cpp
	Layouts/*.cpp
	Settings/*.cpp
	MidiControl/*.cpp
)


# Qt Objects / mocs

FILE( GLOB moc_files
	"${ORZABAL_ROOT_PATH}/lib-src/QtAwesome/*.h"
	Widget/AbstractDropdown.h
	Widget/AbstractIODropdown.h
	Widget/InstrumentDropdown.h
	Widget/Patchbay.h
	Widget/PatchbayPlugin.h
	Widget/SimpleLayout.h
	Widget/SingleInstrument.h
	Widget/InputDropdown.h
	Widget/OutputDropdown.h
	Widget/TreeNode.h
	LV2/IOPortChanger.h
	LV2/PresetDropdown.h
	LV2/WindowLayout.h
	Settings/Layout.h
	MainWindow.h
	MidiControl/Control.h
	MidiControl/ControlPort.h
	MidiControl/ControlPortValue.h
)


# SBC Specific

if (ORZA_BUILD_TYPE STREQUAL "Pi")
	file(GLOB orzabal_pi_files "Pi/*.cpp")
	list(APPEND orzabal.qt_SRC ${orzabal_pi_files})

	list(APPEND moc_files Pi/Layout.h)
endif()


QT5_WRAP_CPP( MY_MOCED_FILES ${moc_files} )


# CMake Config type
# Pi for fullscreen
# Linux default

if( ORZA_BUILD_TYPE STREQUAL "Pi" )
	set( ORZABAL_QT_BUILD_TYPE "Pi" )
else()
	set( ORZABAL_QT_BUILD_TYPE "Linux" )
endif()

configure_file(Config/BuildType.h.in Config/BuildType.h)


# Default layout

add_definitions(-DORZABAL_QT_DEFAULT_LAYOUT=${ORZABAL_QT_DEFAULT_LAYOUT})

if( "${ORZABAL_QT_DEFAULT_LAYOUT}" STREQUAL "" )
	set( ORZABAL_QT_DEFAULT_LAYOUT "InstrumentEffect" )
endif()


# Defaults configure

configure_file(Config/Defaults.h.in Config/Defaults.h)


# Main executable

add_executable(orzabal.qt ${orzabal.qt_SRC} ${RESOURCES} ${MY_MOCED_FILES} )

target_link_libraries( orzabal.qt
	PUBLIC
	dl
	jack
	liborza-common-jack
	liborza-qt
	liborza-common-plugin
	orzabal-common-network
	orzabal-cli
	Qt5::Widgets
	Qt5::Core
	Qt5::Gui
	Qt5::Qml
	${Boost_LIBRARIES}
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
