# Common lib
project(gabrielo-common CXX)


#set( GABRIELO_GUI_INCLUDE_FILES )
file( GLOB
    GABRIELO_COMMON_INCLUDE_FILES
    "*.cpp"
    "*.h"
    "LADSPA/*.h"
    "LADSPA/*.cpp"
)


## Building
# create gabrielo-gui library
add_library(gabrielo-common-lib SHARED ${GABRIELO_COMMON_INCLUDE_FILES} )

set_target_properties(gabrielo-common-lib PROPERTIES LINKER_LANGUAGE CXX)


## Installing
# add installation for target farweller

install(TARGETS gabrielo-common-lib
    DESTINATION "${GABRIELO_LIB_PATH}"
)


# copy public include files
#install(FILES
    #${GABRIELO_COMMON_INCLUDE_FILES}
    #DESTINATION ${GABRIELO_LIB_PATH}/gabrielo-common)


## create export file which can be imported by other cmake projects
#install(EXPORT gabrielo-common_export
    #NAMESPACE sample::
    #DESTINATION lib/cmake/gabrielo-common_lib
    #)
