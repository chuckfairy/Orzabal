#Src test

# test project
project(orzabal-tests CXX)


## LADSPA

add_executable( ladspalist LADSPA.cpp )

# We have to link
target_link_libraries( ladspalist
    PUBLIC orzabal-common
)

target_include_directories( ladspalist PUBLIC "../src/common" )

install( TARGETS
   ladspalist

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)


## LV2

add_executable( lv2test.run LV2.cpp )

# We have to link
target_link_libraries( lv2test.run
    PUBLIC orzabal-common-lv2 orzabal-common
    suil-0 jack sratom-0 serd-0 sord-0
    orzabal-common-jack
    orzabal-common-lv2
    "/usr/local/lib/liblilv-0.so"
)

target_include_directories( lv2test.run
    PUBLIC
    "../../src/common"
    "/usr/include/suil-0" "/usr/local/include/sratom-0"
    "/usr/local/include/serd-0" "/usr/include/sord-0"
)

install( TARGETS
   lv2test.run

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)


## Jack backend

#add_executable( jacktest Jack.cpp )

#target_link_libraries( jacktest
    #PUBLIC orzabal-backend-server orzabal-backend-midi jack asound sndfile
#)


#target_include_directories( jacktest PUBLIC ${JACK_INCLUDE_DIRS} )

#target_include_directories( jacktest PUBLIC "../src/backend" )

#install( TARGETS
   #jacktest

   #RUNTIME DESTINATION bin
   #LIBRARY DESTINATION lib
   #ARCHIVE DESTINATION lib
#)
