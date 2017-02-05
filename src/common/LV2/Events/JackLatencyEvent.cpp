/**
 * JackCallback event for jack
 *
 */
#include <jack/jack.h>

#include "JackLatencyEvent.h"
#include "Host.h"

namespace LV2 {


/**
 * Main dispatch, uses plugin as route
 *
 */

void JackLatencyEvent::run( void * o ) {

    _Patchbay->updateJackLatency( o );

};

};
