/**
 * JackCallback event for jack
 *
 */
#include <jack/jack.h>

#include "UpdateEvent.h"
#include <Jack/Patchbay.h>

namespace Jack {


/**
 * Main dispatch, uses plugin as route
 *
 */

void UpdateEvent::run( void * o ) {

    _Patchbay->updateJack( (jack_nframes_t * ) o );

};

};
