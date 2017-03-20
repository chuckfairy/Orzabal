/**
 * Jack host base
 *
 */
#pragma once

#include <jack/jack.h>

#include <Audio/Patchbay.h>

#include "Host.h"
#include "ServerStandalone.h"


namespace Jack {

/**
 * Class forwards
 */

class Server;


/**
 * Construct
 */

class Patchbay : public Audio::Patchbay, public ServerStandalone {

    protected:

        Server * _Server;


    public:

        explicit Patchbay( jack_client_t * );


        /**
         * Server related
         */

        void setServer( Server * );


        /**
         * host extensions
         *
         */

        unsigned int getSampleRate() {

            return jack_get_sample_rate( _jackClient );
        };

        int getBufferSize() {

            return jack_get_buffer_size( _jackClient );

        };

        int getMidiBufferSize() {

            return jack_port_type_get_buffer_size( _jackClient, JACK_DEFAULT_MIDI_TYPE );

        };


        /**
         * Connectors
         */

        void connectPluginPorts( Audio::Plugin * );

        void connectPluginAudioPorts( Audio::Plugin * );

        void connectPluginMidiPorts( Audio::Plugin * );

};

};
