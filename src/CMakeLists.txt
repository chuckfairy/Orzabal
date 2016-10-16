find_package(JACK)
set_package_properties(JACK PROPERTIES TYPE REQUIRED PURPOSE "Enables JACK plugin")

include_directories(${JACK_INCLUDE_DIRS})
add_definitions(${JACK_DEFINITIONS})
#add_library(vcable-jack MODULE jack.c)

add_executable( client main.c )
add_executable( sine sine.cpp )

target_link_libraries( client PRIVATE ${JACK_LIBRARIES})
target_link_libraries( sine PRIVATE ${JACK_LIBRARIES})

install( TARGETS
    client

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)

install( TARGETS
    sine

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
