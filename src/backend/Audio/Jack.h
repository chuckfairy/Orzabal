/**
 * Jack audio mod
 *
 */
#pragma once

#include <vector>

#include <jack/jack.h>

#include <Audio/Host.h>
#include <Audio/Plugin.h>
#include <Audio/Port.h>


using std::vector;


/**
 * Midi Alsa extended class
 *
 */

namespace Audio {

class Jack : public Host {

    private:

        const char * _name = "gabrielo-audio";


        /**
         * Jack input port
         */

        jack_port_t * _outputLeft;

        jack_port_t * _outputRight;

        const char * _outputLeftName = "input-l";

        const char * _outputRightName = "input-r";


        /**
         * Jack input port
         */

        jack_port_t * _inputLeft;

        jack_port_t * _inputRight;

        const char * _inputLeftName = "input-l";

        const char * _inputRightName = "input-r";


        /**
         * Jack client pointer
         */

        jack_client_t * _jackClient;



    public:

        Jack();

        Jack( jack_client_t * j );

        void start();

        void setJackClient( jack_client_t * j ) {

            _jackClient = j;

            createPorts();

        };

        void createPorts();

        vector<Port> getPorts();

};

};
