/**
 * Jack host impl
 *
 */

#include "Patchbay.h"


namespace Jack {


/**
 * Construct
 */

Patchbay::Patchbay( jack_client_t * c ) {

    setJackClient( c );

};

};
