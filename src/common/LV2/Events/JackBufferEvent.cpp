/**
 * JackCallback event for jack
 *
 */
#include <jack/jack.h>

#include "JackBufferEvent.h"
#include "Host.h"

namespace LV2 {


/**
 * Main dispatch, uses plugin as route
 *
 */

void JackBufferEvent::run( void * o ) {

    _Patchbay->updateBufferSize( (jack_nframes_t * ) o );

};

};
