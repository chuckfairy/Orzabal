project(gabrielo-backend-midi CXX)

find_package( JACK )
#find_package( gabrielo-common )
set_package_properties( JACK PROPERTIES TYPE REQUIRED PURPOSE "Enables JACK plugin" )


file( GLOB
    GABRIELO_MIDI_INCLUDE_FILES
    "*.cpp"
    "*.h"
)


## Building
# create gabrielo-backend-common library
add_library( gabrielo-backend-midi SHARED ${GABRIELO_MIDI_INCLUDE_FILES} )

target_link_libraries( gabrielo-backend-midi PUBLIC asound gabrielo-common )
target_include_directories( gabrielo-backend-midi PUBLIC "../../common" )

set_target_properties( gabrielo-backend-midi PROPERTIES LINKER_LANGUAGE CXX )

install(TARGETS gabrielo-backend-midi EXPORT gabrielo-backend-midi-export
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    DESTINATION "${GABRIELO_LIB_PATH}"
    INCLUDES DESTINATION include
)
