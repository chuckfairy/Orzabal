#Src test

# test project
project(gabrielo-tests CXX)


## LADSPA

add_executable( ladspalist LADSPA.cpp )

# We have to link
target_link_libraries( ladspalist
    PUBLIC gabrielo-common
)

target_include_directories( ladspalist PUBLIC "../src/common" )

install( TARGETS
   ladspalist

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)


## LV2

add_executable( lv2list LV2.cpp )

# We have to link
target_link_libraries( lv2list
    PUBLIC gabrielo-common-lv2 gabrielo-common
    "/usr/local/lib/liblilv-0.so"
)

target_include_directories( lv2list PUBLIC ../../src/common )

install( TARGETS
   lv2list

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)


## Jack backend

add_executable( jacktest Jack.cpp )

# We have to link
target_link_libraries( jacktest
    PUBLIC gabrielo-backend-server gabrielo-backend-midi jack asound sndfile
)


target_include_directories( jacktest PUBLIC ${JACK_INCLUDE_DIRS} )

target_include_directories( jacktest PUBLIC "../src/backend" )

install( TARGETS
   jacktest

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
