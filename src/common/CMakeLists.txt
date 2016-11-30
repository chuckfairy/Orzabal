# Common lib
project(gabrielo-common CXX)


#set( GABRIELO_GUI_INCLUDE_FILES )
file( GLOB
    GABRIELO_COMMON_INCLUDE_FILES
    "*.cpp"
    "*.h"
    #"LADSPA/*.h"
    #"LADSPA/*.cpp"

    "LADSPA/LADSPAPlugin.cpp"
    "LADSPA/LADSPAPlugin.h"
    "LADSPA/LADSPASearch.cpp"
    "LADSPA/LADSPASearch.h"
    "LADSPA/LADSPAPort.h"

    "Audio/Plugin.cpp"
    "Audio/Plugin.h"
    "Audio/Search.cpp"
    "Audio/Search.h"
    "Audio/Port.h"

    "Midi/Device.h"
)


## Building
# create gabrielo-gui library
add_library( gabrielo-common ${GABRIELO_COMMON_INCLUDE_FILES} )

target_link_libraries( gabrielo-common dl )

add_subdirectory( LV2 )

#target_include_directories( gabrielo-common PUBLIC LV2 )

target_link_libraries( gabrielo-common
    "/usr/local/lib/liblilv-0.so"
)

target_include_directories( gabrielo-common PUBLIC "/usr/local/include/lilv-0" )

set_target_properties(gabrielo-common PROPERTIES LINKER_LANGUAGE CXX)


## Installing
# add installation for target farweller

install(TARGETS gabrielo-common EXPORT gabrielo-common-export
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    DESTINATION "${GABRIELO_LIB_PATH}"
    INCLUDES DESTINATION include
)


# copy public include files
install(FILES
    LADSPA/LADSPAPort.h
    DESTINATION "${GABRIELO_LIB_PATH}/gabrielo-common"
)


## create export file which can be imported by other cmake projects
install(EXPORT gabrielo-common-export
    DESTINATION lib/cmake/gabrielo-common-lib
)
