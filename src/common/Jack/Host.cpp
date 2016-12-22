/**
 * Jack host impl
 *
 */


#include "Host.h"

namespace Jack {


/**
 * Construct
 */

Host::Host( jack_client_t * c ) {

    setJackClient( c );

};

};
