/**
 * Jack midi host
 */
#pragma once

#include <vector>

#include <jack/jack.h>
#include <jack/types.h>
#include <jack/midiport.h>

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

    float fromVal = .0;
    float toVal = .0;

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

        void addInput( jack_port_t * );

        void addOutput( jack_port_t * );


        /**
         * Default connector helpers
         */

        void connectDefaults();

        void update( jack_nframes_t );

        void updateEvents( jack_nframes_t );

        void updateEventPort( jack_nframes_t, jack_port_t * );


    private:

        Server * _Server;

        vector<jack_port_t*> _inputPorts;

        vector<jack_port_t*> _outputPorts;

};

};
