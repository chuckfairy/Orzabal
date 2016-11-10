# Audio common lib
project(gabrielo-common-audio CXX)


file( GLOB
    GABRIELO_AUDIO_INCLUDE_FILES
    "*.h"
)


## Building
# create gabrielo-gui library
add_library(gabrielo-common-audio SHARED ${GABRIELO_AUDIO_INCLUDE_FILES} )

set_target_properties(gabrielo-common-audio PROPERTIES LINKER_LANGUAGE CXX)


## Installing
# add installation for target farweller

install(TARGETS gabrielo-common-audio
    DESTINATION "${GABRIELO_LIB_PATH}"
)


# copy public include files
#install(FILES
    #${GABRIELO_GUI_INCLUDE_FILES}
    #DESTINATION ${GABRIELO_LIB_PATH}/gabrielo-common-audio)


## create export file which can be imported by other cmake projects
#install(EXPORT gabrielo-common-audio_export
    #NAMESPACE sample::
    #DESTINATION lib/cmake/gabrielo-common-audio_lib
    #)
