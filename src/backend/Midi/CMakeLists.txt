project(orzabal-backend-midi CXX)

find_package( JACK )
#find_package( orzabal-common )
set_package_properties( JACK PROPERTIES TYPE REQUIRED PURPOSE "Enables JACK plugin" )


file( GLOB
    ORZABAL_MIDI_INCLUDE_FILES
    "*.cpp"
    "*.h"
)


## Building
# create orzabal-backend-common library
add_library( orzabal-backend-midi SHARED ${ORZABAL_MIDI_INCLUDE_FILES} )

target_link_libraries( orzabal-backend-midi PUBLIC asound orzabal-common jack )
target_include_directories( orzabal-backend-midi PUBLIC "../../common" )

set_target_properties( orzabal-backend-midi PROPERTIES LINKER_LANGUAGE CXX )

install(TARGETS orzabal-backend-midi EXPORT orzabal-backend-midi-export
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    DESTINATION "${ORZABAL_LIB_PATH}"
    INCLUDES DESTINATION include
)
