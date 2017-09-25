# Common lib
project(orzabal-common CXX)


# Main config
configure_file(Config/Config.h.in Config/Config.h)

configure_file(Config/PluginTypes.h.in Config/PluginTypes.h)


#set( ORZABAL_GUI_INCLUDE_FILES )
file( GLOB
    ORZABAL_COMMON_INCLUDE_FILES
    "*.cpp"
    "*.h"

    "Util/Dispatcher.h"

    "Audio/Plugin.cpp"
    "Audio/Plugin.h"
    "Audio/Search.cpp"
    "Audio/Search.h"
    "Audio/Port.h"

    "Midi/Device.h"

)


## Building
# create orzabal-gui library
add_library( orzabal-common SHARED ${ORZABAL_COMMON_INCLUDE_FILES} )

target_link_libraries( orzabal-common dl )

#target_include_directories( orzabal-common PUBLIC LV2 )

target_link_libraries( orzabal-common
)

target_include_directories( orzabal-common PUBLIC )

set_target_properties(orzabal-common PROPERTIES LINKER_LANGUAGE CXX)


## Installing
# add installation for target farweller

install( TARGETS
   orzabal-common
   EXPORT orzabal-common
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
