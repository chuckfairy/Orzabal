/**
 * JackCallback event for jack
 *
 */
#include <jack/jack.h>

#include "JackBufferEvent.h"
#include <Jack/Host.h>

namespace Jack {


/**
 * Main dispatch, uses plugin as route
 *
 */

void BufferEvent::run( void * o ) {

    _Patchbay->updateJackBufferSize( o );

};

};
