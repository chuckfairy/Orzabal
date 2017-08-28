/**
 * Client resource impl
 */

#include "Client.h"


namespace Jack { namespace Resource {


static jack_client_t * Client::CLIENT = nullptr;

static jack_options_t Client::JACK_OPTIONS = JackNullOption;


/**
 * Singleton method
 */

static jack_client_t * Client::getInstance() {

    if( Client::CLIENT == nullptr ) {

        _client = jack_client_open(
            Client::JACK_CLIENT_NAME,
            Client::JACK_OPTIONS,
            &Client::JACK_STATUS
        );

    }

    return Client::Client;

};

}; };
