# LV2 cmake

# project
project(gabrielo-common-lv2 CXX)

find_package(Lv2)
find_package(Lilv)


## Installing
# add installation for target farweller

add_executable( gabrielo-common-lv2 lv2ls.c )

# We have to link

target_link_libraries( gabrielo-common-lv2
    "/usr/local/lib/liblilv-0.so"
)

target_include_directories( gabrielo-common-lv2 PUBLIC "/usr/local/include/lilv-0" )

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
