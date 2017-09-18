#Src test

# test project
project(orzabal-tests CXX)

#Setup CMake to run tests
enable_testing()



## LADSPA Inactive ATM ###

#add_executable( ladspalist LADSPA.cpp )

# We have to link
#target_link_libraries( ladspalist
    #PUBLIC orzabal-common
#)

#target_include_directories( ladspalist PUBLIC "../src/common" )

#install( TARGETS
   #ladspalist

   #RUNTIME DESTINATION bin
   #LIBRARY DESTINATION lib
   #ARCHIVE DESTINATION lib
#)
####


#Prep ourselves for compiling boost
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

#I like to keep test files in a separate source directory called test
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Midi/*.cpp
    Jack/*.cpp
    JSON/*.cpp
    CLI/*.cpp
)

#Run through each source
foreach(testSrc ${TEST_SRCS})
    #Extract the filename without an extension (NAME_WE)
    get_filename_component(testName ${testSrc} NAME_WE)

    #Add compile target
    add_executable(${testName} ${testSrc})

    #link to Boost libraries AND your targets and dependencies
    target_link_libraries(${testName} ${Boost_LIBRARIES}
        jack
        orzabal-common-lv2 orzabal-common
        orzabal-common-audio
        orzabal-common-jack
        orzabal-common-lv2
        orzabal-cli
    )

    target_include_directories( ${testName}
        PUBLIC
        "${ORZABAL_ROOT_PATH}/src"
        "${ORZABAL_ROOT_PATH}/lib-src"
        "${ORZABAL_ROOT_PATH}/lib-src/sratom"
        "${ORZABAL_ROOT_PATH}/lib-src/sord"
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
