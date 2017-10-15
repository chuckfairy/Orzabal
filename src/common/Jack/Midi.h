/**
 * Jack midi host
 */
#pragma once

#include <vector>

#include <jack/jack.h>
#include <jack/types.h>

#include <Midi/Control.h>

#include "Port.h"

#include "Host.h"

using std::vector;

using Orza::Midi::ControlPort;
using Orza::Midi::ControlNumber;


namespace Jack {

/**
 * Forwarding
 */

class Server;

struct MidiControlPort : public ControlPort<Port> {

    MidiControlPort( Port * p, ControlNumber num ) :
        ControlPort( p, num )
    {};

};


/**
 * Main class
 */

class Midi : public Host {

    public:

        explicit Midi( Server * );


        /**
         * Main external port getter
         */

        vector<Port> getMidiPorts();

        vector<MidiControlPort*> getMidiControlPorts();


        /**
         * Main port setters
         */

        void addInput( const jack_port_t * );

        void addOutput( const jack_port_t * );


        /**
         * Default connector helpers
         */

        void connectDefaults();


    private:

        Server * _Server;

        vector<const jack_port_t*> _inputPorts;

        vector<const jack_port_t*> _outputPorts;

};

};
