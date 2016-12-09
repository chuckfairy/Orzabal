project(gabrielo-backend-audio CXX)

find_package( JACK )
#find_package( gabrielo-common )
set_package_properties( JACK PROPERTIES TYPE REQUIRED PURPOSE "Enables JACK plugin" )


file( GLOB
    GABRIELO_BACKEND_AUDIO_INCLUDE_FILES
    "*.cpp"
    "*.h"
)


## Building
# create gabrielo-backend-common library
add_library( gabrielo-backend-audio SHARED ${GABRIELO_BACKEND_AUDIO_INCLUDE_FILES} )


target_link_libraries( gabrielo-backend-audio PUBLIC
    asound gabrielo-common gabrielo-common-audio jack
)

target_include_directories( gabrielo-backend-audio PUBLIC "../../common" )

set_target_properties( gabrielo-backend-audio PROPERTIES LINKER_LANGUAGE CXX )

install(TARGETS gabrielo-backend-audio EXPORT gabrielo-backend-audio-export
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    DESTINATION "${GABRIELO_LIB_PATH}"
    INCLUDES DESTINATION include
)
