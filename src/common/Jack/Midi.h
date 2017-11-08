/**
 * Jack midi host
 */
#pragma once

#include <vector>

#include <jack/jack.h>
#include <jack/types.h>
#include <jack/midiport.h>

#include <Util/Dispatcher.h>
#include <Midi/Control.h>

#include "Port.h"
#include "MidiEvent.h"
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

class Midi : public Host, public Util::Dispatcher {

    public:

        explicit Midi( Server * );

        static const char * ALL_EVENTS;

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


        void handleEvent( MidiEvent * );

};

};
