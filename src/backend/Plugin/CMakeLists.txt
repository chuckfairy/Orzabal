project(gabrielo-backend-plugin CXX)

find_package( JACK )
#find_package( gabrielo-common )
set_package_properties( JACK PROPERTIES TYPE REQUIRED PURPOSE "Enables JACK plugin" )


file( GLOB
    GABRIELO_BACKEND_PLUGIN_INCLUDE_FILES
    "*.cpp"
    "*.h"
)


## Building
# create gabrielo-backend-common library
add_library( gabrielo-backend-plugin SHARED ${GABRIELO_BACKEND_PLUGIN_INCLUDE_FILES} )


target_link_libraries( gabrielo-backend-plugin PUBLIC
    asound gabrielo-common gabrielo-common-audio jack
)

target_include_directories( gabrielo-backend-plugin PUBLIC "../../common" )

set_target_properties( gabrielo-backend-plugin PROPERTIES LINKER_LANGUAGE CXX )

install(TARGETS gabrielo-backend-plugin EXPORT gabrielo-backend-plugin-export
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    DESTINATION "${GABRIELO_LIB_PATH}"
    INCLUDES DESTINATION include
)
