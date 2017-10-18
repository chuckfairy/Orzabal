# Pi / Single Board exec startup
find_package( ODROID )

# VNC

add_definitions(-DPI_USE_VNC=${PI_USE_VNC})

add_definitions(-DPI_VNC_COMMAND=${PI_VNC_COMMAND})


# Commands

add_definitions(-DORZA_PI_SHUTDOWN_CMD="${ORZA_PI_SHUTDOWN_CMD}")
add_definitions(-DORZA_PI_RESTART_CMD=${ORZA_PI_RESTART_CMD})


if( "${ORZA_PI_SHUTDOWN_CMD}" STREQUAL "" )
    set( ORZA_PI_SHUTDOWN_CMD "sudo shutdown 0" )
endif()

if( "${ORZA_PI_RESTART_CMD}" STREQUAL "" )
    set( ORZA_PI_RESTART_CMD "sudo reboot" )

endif()

configure_file( Config/Commands.h.in Config/Commands.h )


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
)

target_include_directories(
    orzabal_gpio_config
    PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ../common
    "${ORZABAL_ROOT_PATH}/lib-src"
)
