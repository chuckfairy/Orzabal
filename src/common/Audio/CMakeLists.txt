# Audio common lib
project(orzabal-common-audio CXX)


file( GLOB
    ORZABAL_AUDIO_INCLUDE_FILES
    "Config/*.h"
    "*.h"
    "*.cpp"
)

include_directories( "${CMAKE_CURRENT_BINARY_DIR}")

# Configure app data path

add_definitions(-DORZA_DATA_PATH=${ORZA_DATA_PATH})

if( "${ORZA_DATA_PATH}" STREQUAL "" )
    set( ORZABAL_DATA_PATH "${ORZABAL_ROOT_PATH}/data" )
endif()

configure_file(Config/Config.h.in Config/Config.h)


## Building
# create orzabal-gui library
add_library(orzabal-common-audio STATIC ${ORZABAL_AUDIO_INCLUDE_FILES} )

set_target_properties(orzabal-common-audio PROPERTIES LINKER_LANGUAGE CXX)


## Installing
# add installation for target farweller

#install(TARGETS orzabal-common-audio
    #DESTINATION "${ORZABAL_LIB_PATH}"
#)

install( TARGETS
   orzabal-common-audio
   EXPORT orzabal-common-audio
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)


# copy public include files
#install(FILES
    #${ORZABAL_GUI_INCLUDE_FILES}
    #DESTINATION ${ORZABAL_LIB_PATH}/orzabal-common-audio)


## create export file which can be imported by other cmake projects
#install(EXPORT orzabal-common-audio_export
    #NAMESPACE sample::
    #DESTINATION lib/cmake/orzabal-common-audio_lib
    #)
