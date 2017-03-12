/**
 * Shared testing defaults
 */
#pragma once

#include <jack/jack.h>

jack_client_t * testCreateJackClient() {

    return jack_client_open(
        "orzabal-test",
        JackNullOption,
        NULL
    );

};
