# LV2 cmake

# project
project(gabrielo-common-lv2 CXX)

find_package( JACK )

#find_package(Lv2)
#find_package(Lilv)


#set( GABRIELO_LV2_INCLUDE_FILES )
file( GLOB
    GABRIELO_LV2_INCLUDE_FILES
    "include/*.h"
    "include/symap.c"
    "Plugin.cpp"
    "Host.cpp"
    "Search.cpp"
    "UI.cpp"
)


## Building
# create gabrielo-common-lv2 library
add_library(gabrielo-common-lv2 SHARED ${GABRIELO_LV2_INCLUDE_FILES} )

set_target_properties(gabrielo-common-lv2 PROPERTIES LINKER_LANGUAGE CXX)


## Installing
# add installation for target farweller

install(TARGETS gabrielo-common-lv2
    DESTINATION "${GABRIELO_LIB_PATH}"
)

include_directories( "/usr/local/lib" )

target_link_libraries( gabrielo-common-lv2
    lilv-0 suil-0 jack sratom-0 serd-0 sord-0
    gabrielo-common-jack
)

target_include_directories( gabrielo-common-lv2
    PUBLIC "/usr/local/include/lilv-0" "/usr/include/suil-0" "/usr/local/include/sratom-0"
    "/usr/local/include/serd-0" "/usr/include/sord-0"
    ".."
)

install( TARGETS
   gabrielo-common-lv2

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
