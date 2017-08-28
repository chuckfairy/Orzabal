# CLI common lib
project(orzabal-cli CXX)


file( GLOB
    ORZABAL_CLI_INCLUDE_FILES
    "*.h"
    "*.cpp"
)


## Building
# create orzabal-gui library
add_library(orzabal-cli SHARED ${ORZABAL_CLI_INCLUDE_FILES} )

set_target_properties(orzabal-cli PROPERTIES LINKER_LANGUAGE CXX)


## Installing

#install(TARGETS orzabal-cli
    #DESTINATION "${ORZABAL_LIB_PATH}"
#)

install( TARGETS
   orzabal-cli
   EXPORT orzabal-cli
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)


# copy public include files
#install(FILES
    #${ORZABAL_GUI_INCLUDE_FILES}
    #DESTINATION ${ORZABAL_LIB_PATH}/orzabal-cli)


## create export file which can be imported by other cmake projects
#install(EXPORT orzabal-cli_export
    #NAMESPACE sample::
    #DESTINATION lib/cmake/orzabal-cli_lib
    #)
