/**
 * JackCallback event for jack
 *
 */
#include <jack/jack.h>

#include "LatencyEvent.h"
#include <Jack/Patchbay.h>

namespace Jack {


/**
 * Main dispatch, uses plugin as route
 *
 */

void LatencyEvent::run( void * o ) {

    _Patchbay->updateJackLatency( o );

};

};
