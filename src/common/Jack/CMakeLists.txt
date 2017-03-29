project(orzabal-common-jack CXX)

find_package( JACK )
#find_package( orzabal-common )
set_package_properties( JACK PROPERTIES TYPE REQUIRED PURPOSE "Enables JACK plugin" )


file( GLOB
    ORZABAL_BACKEND_AUDIO_INCLUDE_FILES
    "*.cpp"
    "*.h"
    "Events/*.cpp"
)


## Building
# create orzabal-backend-common library
add_library( orzabal-common-jack SHARED ${ORZABAL_BACKEND_AUDIO_INCLUDE_FILES} )


target_link_libraries( orzabal-common-jack PUBLIC
    asound orzabal-common orzabal-common-audio jack
)

include_directories( orzabal-common-jack INSTALL_INTERFACE "../" )

set_target_properties( orzabal-common-jack PROPERTIES LINKER_LANGUAGE CXX )

#install(TARGETS orzabal-common-jack EXPORT orzabal-common-jack-export
    #RUNTIME DESTINATION bin
    #ARCHIVE DESTINATION lib
    #LIBRARY DESTINATION lib
    #DESTINATION "${ORZABAL_LIB_PATH}"
    #INCLUDES DESTINATION include
#)

set_target_properties(orzabal-common-jack PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

install( TARGETS
   orzabal-common-jack
   EXPORT orzabal-common-jack
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
