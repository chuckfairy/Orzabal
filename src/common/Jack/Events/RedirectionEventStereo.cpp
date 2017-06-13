/**
 * Host redirection implementation
 */
#include <inttypes.h>

#include <jack/types.h>

#include <Jack/StereoHostInterface.h>
#include "RedirectionEventStereo.h"

namespace Jack {

/**
 * Constructs
 */

RedirectionEventStereo::RedirectionEventStereo( StereoHostInterface * h ) {

    _Host = h;

};


/**
 * Main runner
 */

void RedirectionEventStereo::run( void * data ) {

    _Host->redirectInput( (jack_nframes_t) (uintptr_t) data );

};

};
