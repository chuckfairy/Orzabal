/**
 * Server standalone trait setting
 *
 */
#pragma once

#include <jack/jack.h>

#include <Util/Dispatcher.h>


namespace Jack {

class ServerStandalone {

    protected:

        /**
         * Host client pointer
         */

        jack_client_t * _jackClient = nullptr;


        /**
         * Construct viable only through extensions
         */

        ServerStandalone( jack_client_t * c ) :
            _jackClient( c )
        {
        };


    public:

        /**
         * main jack client from server
         */

        void setJackClient( jack_client_t * j ) {

            _jackClient = j;

        };

        jack_client_t * getJackClient() {

            return _jackClient;

        };


        /**
         * Main server setting
         */

        void setAsStandalone();

};

};
