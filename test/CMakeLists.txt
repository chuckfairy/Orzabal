#Src test

# test project
project(gabrielo-tests CXX)


## Installing
# add installation for target farweller

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
