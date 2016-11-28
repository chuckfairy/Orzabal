project(gabrielo-backend CXX)

find_package( JACK )
set_package_properties( JACK PROPERTIES TYPE REQUIRED PURPOSE "Enables JACK plugin" )

include_directories( ${JACK_INCLUDE_DIRS} )
add_definitions( ${JACK_DEFINITIONS} )

add_subdirectory( Server )
add_subdirectory( Midi )
