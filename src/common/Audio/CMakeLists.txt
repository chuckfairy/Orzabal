# Audio common lib
project(orzabal-common-audio CXX)


file( GLOB
    ORZABAL_AUDIO_INCLUDE_FILES
    "*.h"
    "*.cpp"
)


## Building
# create orzabal-gui library
add_library(orzabal-common-audio SHARED ${ORZABAL_AUDIO_INCLUDE_FILES} )

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
