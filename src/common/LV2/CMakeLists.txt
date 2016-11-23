# LV2 cmake

# project
project(gabrielo-common-lv2 CXX)

#find_package(Lv2)
#find_package(Lilv)


## Installing
# add installation for target farweller

#add_executable( gabrielo-common-lv2 lv2ls.c )

## We have to link

#target_link_libraries( gabrielo-common-lv2
    #"/usr/local/lib/liblilv-0.so"
#)

#target_include_directories( gabrielo-common-lv2 PUBLIC "/usr/local/include/lilv-0" "../Audio" )


### VLC lib

## Gui lib
project(gabrielo-common-lv2 CXX)


#set( GABRIELO_LV2_INCLUDE_FILES )
file( GLOB
    GABRIELO_LV2_INCLUDE_FILES
    "Plugin.h"
    "Plugin.cpp"
    "Search.h"
    "Search.cpp"
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

target_link_libraries( gabrielo-common-lv2
    "/usr/local/lib/liblilv-0.so"
)

target_include_directories( gabrielo-common-lv2 PUBLIC "/usr/local/include/lilv-0" ".." )


# copy public include files
#install(FILES
    #${GABRIELO_LV2_INCLUDE_FILES}
    #DESTINATION ${GABRIELO_LIB_PATH}/gabrielo-common-lv2)


## create export file which can be imported by other cmake projects
#install(EXPORT gabrielo-common-lv2_export
    #NAMESPACE sample::
    #DESTINATION lib/cmake/gabrielo-common-lv2_lib
    #)


#IF (LILV_FOUND)
    #INCLUDE_DIRECTORIES(${Lilv_INCLUDE_DIR})
#ELSE()
    #message( FATAL_ERROR "No LILV" )
#ENDIF()

install( TARGETS
   gabrielo-common-lv2

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
