/**
 * Callback event for jack
 *
 */
#pragma once

#include <jack/jack.h>

#include "CallbackEvent.h"
#include "Plugin.h"

namespace LV2 {


/**
 * Main dispatch, uses plugin as route
 *
 */

void CallbackEvent::run( void * o ) {

    _Plugin->updateJack( (jack_nframes_t * ) o );

};

};

};
