/**
 * Jack host base
 *
 */
#pragma once

#include <jack/jack.h>

#include <Audio/Host.h>


namespace Jack {

/**
 * Construct
 */

class Host : public Audio::Host {

    protected:

        jack_client_t * _JackClient;


    public:

        Host( jack_client_t * );


        /**
         * host extensions
         *
         */

        unsigned int getSampleRate() {

            return jack_get_sample_rate( _JackClient );
        };

        int getBufferSize() {

            return jack_get_buffer_size( _JackClient );

        };

        int getMidiBufferSize() {

            return jack_port_type_get_buffer_size( _JackClient, JACK_DEFAULT_MIDI_TYPE );

        };


        /**
         * Jack client related
         *
         */

        void setJackClient( jack_client_t * c ) {

            _JackClient = c;

        };

        jack_client_t * getJackClient() {

            return _JackClient;

        };

};

};
