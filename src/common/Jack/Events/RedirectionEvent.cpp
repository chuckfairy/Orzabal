/**
 * Host redirection implementation
 */
#include <inttypes.h>

#include <jack/types.h>

#include <Jack/Host.h>
#include "RedirectionEvent.h"

namespace Jack {

/**
 * Constructs
 */

RedirectionEvent::RedirectionEvent( Host * h ) {

    _Host = h;

};


/**
 * Main runner
 */

void RedirectionEvent::run( void * data ) {

    _Host->redirectInput( (jack_nframes_t) (uintptr_t) data );

};

};
