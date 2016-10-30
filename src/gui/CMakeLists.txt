# Gui lib
project(gabrielo-gui C CXX)

#set( GABRIELO_GUI_INCLUDE_FILES )
file( GLOB
    GABRIELO_GUI_INCLUDE_FILES
    "*.cpp"
    "*.h"
)


## Building
# create gabrielo-gui library
#add_library(gabrielo-gui-lib SHARED GUI.h )
add_library(gabrielo-gui-lib SHARED ${GABRIELO_GUI_INCLUDE_FILES} )

set_target_properties(gabrielo-gui-lib PROPERTIES LINKER_LANGUAGE CXX)



# setup include directories
#target_include_directories(gabrielo-gui-lib PUBLIC
    #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    #$<INSTALL_INTERFACE:include>
    #)


# setup export preprocessor definitions
#target_compile_definitions(gabrielo-gui_lib PRIVATE FAREWELLER_EXPORTS)
#target_compile_definitions(gabrielo-gui_lib INTERFACE FAREWELLER_IMPORTS)


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
