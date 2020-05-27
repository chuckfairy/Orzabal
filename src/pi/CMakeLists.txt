# Pi / Single Board exec startup
find_package( ODROID )

# VNC
add_definitions(-DPI_USE_VNC=${PI_USE_VNC})
add_definitions(-DPI_VNC_COMMAND=${PI_VNC_COMMAND})


# Commands

add_definitions(-DORZA_PI_SHUTDOWN_CMD="${ORZA_PI_SHUTDOWN_CMD}")
add_definitions(-DORZA_PI_RESTART_CMD=${ORZA_PI_RESTART_CMD})
add_definitions(-DORZA_PI_KEYBOARD_CMD=${ORZA_PI_KEYBOARD_CMD})


if( "${ORZA_PI_SHUTDOWN_CMD}" STREQUAL "" )
    set( ORZA_PI_SHUTDOWN_CMD "sudo shutdown 0" )
endif()

if( "${ORZA_PI_RESTART_CMD}" STREQUAL "" )
    set( ORZA_PI_RESTART_CMD "sudo reboot" )
endif()

if( "${ORZA_PI_KEYBOARD_CMD}" STREQUAL "" )
    set( ORZA_PI_KEYBOARD_CMD "nohup onboard" )
endif()


# Defaults

if( ${IS_ODROID} )
    file( STRINGS "./Resource/odroid-c2_800x600.json" ORZA_PI_PIN_CONFIG_JSON
        NEWLINE_CONSUME
    )
else()
    file( STRINGS "./Resource/effect_pin_layout.json" ORZA_PI_PIN_CONFIG_JSON
        NEWLINE_CONSUME
    )
endif()

configure_file( Config/Defaults.h.in Config/Defaults.h )


# pin gpio config exec

file(
    GLOB
    SRC_FILES
    *.cpp
)

add_executable(orzabal_gpio_config ${SRC_FILES} )

target_link_libraries(orzabal_gpio_config
    PUBLIC
    wiringPi
    pthread
	rt
	crypt
	iw
)

target_include_directories(
    orzabal_gpio_config
    PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ../common
    "${ORZABAL_ROOT_PATH}/lib-src"
    "${ORZABAL_ROOT_PATH}/lib-src/liborza/lib-src"
    "${ORZABAL_ROOT_PATH}/lib-src/liborza/src"
)

install( TARGETS
   orzabal_gpio_config

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)

install( TARGETS
    orzabal_gpio_config

    DESTINATION /etc/init.d
)


# Vnc Setup
set(NO_VNC_REPO "https://github.com/novnc/noVNC")
set(NO_VNC_LOCATION "${ORZABAL_ROOT_PATH}/lib-src/novnc")


add_definitions(-DVNC_STARTUP_LOCATION="${CMAKE_CURRENT_BINARY_DIR}/vnc_startup.sh")
add_definitions(-DVNC_STOP_LOCATION="${CMAKE_CURRENT_BINARY_DIR}/vnc_stop.sh")

configure_file( vnc_install.sh.in vnc_install.sh )
configure_file( vnc_startup.sh.in vnc_startup.sh )
configure_file( vnc_stop.sh.in vnc_stop.sh )



# Vnc Install
set(vnc_install_cmd "${CMAKE_CURRENT_BINARY_DIR}/vnc_install.sh")
message(STATUS "Executing ${vnc_install_cmd}")

execute_process(
	COMMAND "${vnc_install_cmd}"
	ERROR_VARIABLE vnc_install_error
)

if (NOT vnc_install_error STREQUAL "")
	message(SEND_ERROR ${vnc_install_error})
endif()


# Config setup
configure_file( Config/Commands.h.in Config/Commands.h )

# Pins
if (UNIX)
    #install(
        #FILES pin_startup
        #DESTINATION /etc/init.d/
        #PERMISSIONS OWNER_READ OWNER_EXECUTE OWNER_WRITE GROUP_EXECUTE GROUP_READ WORLD_READ WORLD_EXECUTE
    #)
endif()
