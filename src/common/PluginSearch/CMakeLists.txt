# project
project(orzabal-common-plugin CXX)

# Main files

file( GLOB ORZABAL_PLUGIN_SEARCH_INCLUDE_FILES
    "*.cpp"
)


## Building
add_library(orzabal-common-plugin STATIC ${ORZABAL_PLUGIN_SEARCH_INCLUDE_FILES} )

set_target_properties(orzabal-common-plugin PROPERTIES LINKER_LANGUAGE CXX)


## Installing
# add installation for target farweller

install(TARGETS orzabal-common-plugin
    DESTINATION "${ORZABAL_LIB_PATH}"
)


# LV2 Check

if( ORZABAL_HAS_LV2 )

    set( ORZABAL_PLUGIN_SEARCH_INCLUDE_DIRS
        ${ORZABAL_LV2_INCLUDE_DIRS}
        ${ORZABAL_ROOT_PATH}/lib-src/lilv
        ${ORZABAL_ROOT_PATH}/lib-src/suil
        ${ORZABAL_ROOT_PATH}/lib-src/sord
        ${ORZABAL_ROOT_PATH}/lib-src/serd
        ${ORZABAL_ROOT_PATH}/lib-src/sratom
        ".."
    )

    set( ORZABAL_PLUGIN_SEARCH_LINK_LIBRARIES
        "orzabal-common-lv2"
    )

endif()


# Setup

target_link_libraries( orzabal-common-plugin
    orzabal-common-audio
    orzabal-common-jack
    ${ORZABAL_PLUGIN_SEARCH_LINK_LIBRARIES}
)

target_include_directories( orzabal-common-plugin PUBLIC
    ".."
    ${ORZABAL_PLUGIN_SEARCH_INCLUDE_DIRS}
    ${ORZABAL_SRC_PATH}
    ${CMAKE_CURRENT_BINARY_DIR}
)

install( TARGETS
   orzabal-common-plugin

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
