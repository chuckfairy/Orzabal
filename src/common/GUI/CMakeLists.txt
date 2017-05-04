# Gui lib
project(orzabal-gui CXX)


#set( ORZABAL_GUI_INCLUDE_FILES )
file( GLOB
    ORZABAL_GUI_INCLUDE_FILES
    "*.cpp"
    "*.h"
)


## Building
# create orzabal-gui library
add_library(orzabal-gui SHARED ${ORZABAL_GUI_INCLUDE_FILES} )

set_target_properties(orzabal-gui PROPERTIES LINKER_LANGUAGE CXX)


## Installing
# add installation for target farweller

install(TARGETS orzabal-gui
    DESTINATION "${ORZABAL_LIB_PATH}"
)


# copy public include files
#install(FILES
    #${ORZABAL_GUI_INCLUDE_FILES}
    #DESTINATION ${ORZABAL_LIB_PATH}/orzabal-gui)


## create export file which can be imported by other cmake projects
#install(EXPORT orzabal-gui_export
    #NAMESPACE sample::
    #DESTINATION lib/cmake/orzabal-gui_lib
    #)
