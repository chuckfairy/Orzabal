/**
 * Jack midi host
 */
#pragma once

#include <vector>

#include <jack/jack.h>
#include <jack/types.h>

#include "Host.h"

using std::vector;


namespace Jack {

/**
 * Forwarding
 */

class Server;


/**
 * Main class
 */

class Midi : public Host {

    private:

        Server * _Server;

        vector<const jack_port_t*> _inputPorts;

        vector<const jack_port_t*> _outputPorts;


    public:

        explicit Midi( Server * );


        /**
         * Main external port getter
         */

        vector<Port> getMidiPorts();


        /**
         * Main port setters
         */

        void addInput( const jack_port_t * );
        void addOutput( const jack_port_t * );


        /**
         * Default connector helpers
         */

        void connectDefaults();

};

};
