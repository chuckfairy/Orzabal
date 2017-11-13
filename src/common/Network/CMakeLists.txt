# network common lib
project(orzabal-common-network CXX)


file( GLOB
    ORZABAL_NETWORK_INCLUDE_FILES
    "*.cpp"
)

include_directories( "${CMAKE_CURRENT_BINARY_DIR}" "../" )


## Building
# create orzabal-gui library
add_library(orzabal-common-network STATIC ${ORZABAL_NETWORK_INCLUDE_FILES} )

target_link_libraries(orzabal-common-network PUBLIC iw)

set_target_properties(orzabal-common-network PROPERTIES LINKER_LANGUAGE CXX)


install( TARGETS
   orzabal-common-network
   EXPORT orzabal-common-network
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
