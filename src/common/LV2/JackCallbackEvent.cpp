/**
 * JackCallback event for jack
 *
 */
#include <jack/jack.h>

#include "JackCallbackEvent.h"
#include "Host.h"

namespace LV2 {


/**
 * Main dispatch, uses plugin as route
 *
 */

void JackCallbackEvent::run( void * o ) {

    _Patchbay->updateJack( (jack_nframes_t * ) o );

};

};
