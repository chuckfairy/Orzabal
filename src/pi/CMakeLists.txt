# Pi exec startup

# Defs

add_definitions(-DPI_USE_VNC=${PI_USE_VNC})

add_definitions(-DPI_VNC_COMMAND=${PI_VNC_COMMAND})

add_definitions(-DORZA_PI_SHUTDOWN_CMD="${ORZA_PI_SHUTDOWN_CMD}")
add_definitions(-DORZA_PI_RESTART_CMD=${ORZA_PI_RESTART_CMD})


if( "${ORZA_PI_SHUTDOWN_CMD}" STREQUAL "" )
    set( ORZA_PI_SHUTDOWN_CMD "sudo shutdown 0" )
endif()

if( "${ORZA_PI_RESTART_CMD}" STREQUAL "" )
    set( ORZA_PI_RESTART_CMD "sudo reboot" )

endif()

configure_file( Config/Commands.h.in Config/Commands.h )
