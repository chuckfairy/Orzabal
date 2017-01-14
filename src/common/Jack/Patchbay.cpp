/**
 * Jack host impl
 *
 */
#include "Server.h"
#include "Patchbay.h"


namespace Jack {


/**
 * Construct
 */

Patchbay::Patchbay( jack_client_t * c ) {

    setJackClient( c );

};


/**
 * Server related
 */

void Patchbay::setServer( Server * s ) {

    _Server = s;

};

};
