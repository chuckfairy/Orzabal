/**
 * Client resource impl
 */

#include "Client.h"


namespace Jack { namespace Resource {

/**
 * Static props
 */

const char * Client::JACK_CLIENT_NAME = "orzabal";

jack_client_t * Client::CLIENT = nullptr;

jack_options_t Client::JACK_OPTIONS = JackNullOption;

jack_status_t Client::JACK_STATUS;


/**
 * Singleton method
 */

jack_client_t * Client::getInstance() {

    if( Client::CLIENT == nullptr ) {

        Client::CLIENT = jack_client_open(
            Client::JACK_CLIENT_NAME,
            Client::JACK_OPTIONS,
            &Client::JACK_STATUS
        );

    }

    return Client::CLIENT;

};

}; };
