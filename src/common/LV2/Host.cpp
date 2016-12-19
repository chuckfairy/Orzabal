/**
 * LV2 Host extended from Jack
 *
 */
#pragma once

#include <Jack/Host.h>

namespace LV2 {


/**
 * Construct
 */

Host( jack_client_t * c ) : Jack::Host( c ) {

    LilvWorld * _lilvWorld = lilv_world_new();
    lilv_world_load_all( _lilvWorld );

};

};
