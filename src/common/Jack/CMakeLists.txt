project(gabrielo-common-jack CXX)

find_package( JACK )
#find_package( gabrielo-common )
set_package_properties( JACK PROPERTIES TYPE REQUIRED PURPOSE "Enables JACK plugin" )


file( GLOB
    GABRIELO_BACKEND_AUDIO_INCLUDE_FILES
    "*.cpp"
    "*.h"
    "Events/*.cpp"
)


## Building
# create gabrielo-backend-common library
add_library( gabrielo-common-jack SHARED ${GABRIELO_BACKEND_AUDIO_INCLUDE_FILES} )


target_link_libraries( gabrielo-common-jack PUBLIC
    asound gabrielo-common gabrielo-common-audio jack
)

target_include_directories( gabrielo-common-jack PUBLIC "../" )

set_target_properties( gabrielo-common-jack PROPERTIES LINKER_LANGUAGE CXX )

install(TARGETS gabrielo-common-jack EXPORT gabrielo-common-jack-export
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    DESTINATION "${GABRIELO_LIB_PATH}"
    INCLUDES DESTINATION include
)
