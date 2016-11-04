# Gui lib
project(gabrielo-gui CXX)


#set( GABRIELO_GUI_INCLUDE_FILES )
file( GLOB
    GABRIELO_GUI_INCLUDE_FILES
    "*.cpp"
    "*.h"
)


## Building
# create gabrielo-gui library
add_library(gabrielo-gui-lib SHARED ${GABRIELO_GUI_INCLUDE_FILES} )

set_target_properties(gabrielo-gui-lib PROPERTIES LINKER_LANGUAGE CXX)


## Installing
# add installation for target farweller

install(TARGETS gabrielo-gui-lib
    DESTINATION "${GABRIELO_LIB_PATH}"
)


# copy public include files
#install(FILES
    #${GABRIELO_GUI_INCLUDE_FILES}
    #DESTINATION ${GABRIELO_LIB_PATH}/gabrielo-gui)


## create export file which can be imported by other cmake projects
#install(EXPORT gabrielo-gui_export
    #NAMESPACE sample::
    #DESTINATION lib/cmake/gabrielo-gui_lib
    #)
