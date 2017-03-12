#Src test

# test project
project(orzabal-tests CXX)

#Setup CMake to run tests
enable_testing()


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


#Prep ourselves for compiling boost
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

#I like to keep test files in a separate source directory called test
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Jack/*.cpp)

#Run through each source
foreach(testSrc ${TEST_SRCS})
    #Extract the filename without an extension (NAME_WE)
    get_filename_component(testName ${testSrc} NAME_WE)

    #Add compile target
    add_executable(${testName} ${testSrc})

    #link to Boost libraries AND your targets and dependencies
    target_link_libraries(${testName} ${Boost_LIBRARIES}
        orzabal-common-lv2 orzabal-common
        suil-0 jack sratom-0 serd-0 sord-0
        orzabal-common-jack
        orzabal-common-lv2
        "/usr/local/lib/liblilv-0.so"
    )

    target_include_directories( ${testName}
        PUBLIC
        "../../src/common"
        "/usr/include/suil-0" "/usr/local/include/sratom-0"
        "/usr/local/include/serd-0" "/usr/include/sord-0"
    )

    #I like to move testing binaries into a testBin directory
    set_target_properties(${testName} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/testBin)

    #Finally add it to test execution -
    #Notice the WORKING_DIRECTORY and COMMAND
    add_test(NAME ${testName}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )
endforeach(testSrc)


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
