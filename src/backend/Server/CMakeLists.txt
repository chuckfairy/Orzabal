project(gabrielo-backend-server CXX)

find_package( JACK )
set_package_properties( JACK PROPERTIES TYPE REQUIRED PURPOSE "Enables JACK plugin" )


file( GLOB
    GABRIELO_SERVER_INCLUDE_FILES
    "*.cpp"
    "*.h"
)


## Building
# create gabrielo-backend-common library
add_library( gabrielo-backend-server SHARED ${GABRIELO_SERVER_INCLUDE_FILES} )

target_link_libraries( gabrielo-backend-server PUBLIC gabrielo-backend-audio )
target_include_directories( gabrielo-backend-server PUBLIC ${JACK_INCLUDE_DIRS} ../ )
add_definitions( ${JACK_DEFINITIONS} )

install(TARGETS gabrielo-backend-server EXPORT gabrielo-backend-server-export
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    DESTINATION "${GABRIELO_LIB_PATH}"
    INCLUDES DESTINATION include
)
