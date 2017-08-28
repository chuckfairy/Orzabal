/**
 * Jack resource client
 *
 */
#pragma once

#include <jack/jack.h>


namespace Jack { namespace Resource {

class Client {

    public:

        static jack_client_t * getInstance();


    private:

        Client() {};
        ~Client() {};

        /**
         * singleton property
         */

        static jack_client_t * CLIENT;

        static jack_options_t JACK_OPTIONS;

        static jack_status_t JACK_STATUS;


};

}; };
