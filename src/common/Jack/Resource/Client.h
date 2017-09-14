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


        /**
         * client helper extensions
         */

        static unsigned int getSampleRate( jack_client_t * c ) {

            return jack_get_sample_rate( c );

        };

        static int getBufferSize( jack_client_t * c ) {

            return jack_get_buffer_size( c );

        };

        static int getMidiBufferSize( jack_client_t * c ) {

            return jack_port_type_get_buffer_size( c, JACK_DEFAULT_MIDI_TYPE );

        };


    private:

        Client() {};
        ~Client() {};

        /**
         * singleton property
         */

        static jack_client_t * CLIENT;

        static const char * JACK_CLIENT_NAME;

        static jack_options_t JACK_OPTIONS;

        static jack_status_t JACK_STATUS;


};

}; };
