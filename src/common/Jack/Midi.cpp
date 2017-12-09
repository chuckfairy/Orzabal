/**
 * Jack midi host
 */
#include "Midi.h"
#include "Server.h"

using Orza::Midi::ControlNumber;
using Orza::Midi::CONTROL_NUMBER_MIN;
using Orza::Midi::CONTROL_NUMBER_MAX;

namespace Jack {

/**
 * Forwarding
 */

class Server;


/**
 * Main class
 */

Midi::Midi( Server * s ) : Host( s ) {

    _Server = s;

};


const char * Midi::ALL_EVENTS = "all";


/**
 * Get ports by input type JackPortIsOutput
 */

vector<Port> Midi::getMidiPorts() {

    return _Server->getAudio()->getPortsByType( JackPortIsOutput, JACK_DEFAULT_MIDI_TYPE );

};


/**
 * Get midi control ports
 */

vector<MidiControlPort*> Midi::getMidiControlPorts() {

    vector<MidiControlPort*> ports;

    //@TODO fix return to be port pointers or move midi ports to repo

    static vector<Port> jackPorts = getMidiPorts();

    vector<Port>::iterator it;

    //ports loop

    for( int size = 0; size < jackPorts.size(); ++ size ) {

        Port * p = static_cast<Port*>(&jackPorts[ size ]);

        //Loop control numbers

        for( int itNum = CONTROL_NUMBER_MIN; itNum <= CONTROL_NUMBER_MAX; ++ itNum ) {

            ControlNumber num = static_cast<ControlNumber>( itNum );

            ports.push_back( new MidiControlPort( p, num ) );

        }

    }

    return ports;

};


/**
 * Main port adders
 */

void Midi::addInput( jack_port_t * port ) {

    _inputPorts.push_back( port );

    vector<jack_port_t*>::iterator it;

    for( it = _outputPorts.begin(); it != _outputPorts.end(); ++ it ) {

        std::cout << "MIDI ADDING MIDI \n\n";

        std::cout <<
            jack_port_name( *it )
            << " "
            << jack_port_name( port )
        ;

        connectJackPort(
            jack_port_name( *it ),
            jack_port_name( port )
        );

    }

};

void Midi::addOutput( jack_port_t * port ) {

    _outputPorts.push_back( port );

    vector<jack_port_t*>::iterator it;

    for( it = _inputPorts.begin(); it != _inputPorts.end(); ++ it ) {

        connectJackPort(
            jack_port_name( port ),
            jack_port_name( *it )
        );

    }

};


/**
 * Midi default connect from main port getter
 */

void Midi::connectDefaults() {

    vector<Port> ports = getMidiPorts();

    if( ports.empty() ) { return; }

    int size = ports.size();

    while( -- size ) {

        addOutput( ports[ size ].jack_port );

    }

};


/**
 * Update
 */

void Midi::update( jack_nframes_t nframes ) {

    updateEvents( nframes );

};


/**
 * Update midi events and listeners
 */

void Midi::updateEvents( jack_nframes_t nframes ) {

    vector<jack_port_t*>::iterator it;

    for( it = _outputPorts.begin(); it != _outputPorts.end(); ++ it ) {

        updateEventPort( nframes, (*it) );

    }

};


/**
 * Update midi events if any for a port
 */

void Midi::updateEventPort( jack_nframes_t nframes, jack_port_t * port ) {

    void * buf = jack_port_get_buffer( port, nframes );

    if( ! buf ) { return; }

    for( uint32_t i = 0; i < jack_midi_get_event_count( buf ); ++ i ) {

        jack_midi_event_t jackEvent;
        int recevied = jack_midi_event_get( &jackEvent, buf, i );

        //Create check event

        if( recevied != 0 ) { continue; }


        MidiEvent * event = new MidiEvent( &jackEvent );

        if( event->type == Orza::Midi::EVENT_UNKNOWN ) { continue; }


        //Handle event

        handleEvent( event );

        dispatch( jack_port_name( port ), (void*) (event) );

    }

};


/**
 * Handle event
 */

void Midi::handleEvent( MidiEvent * event ) {

    void * mesg = (void *) event;

    dispatch( ALL_EVENTS, event );

    dispatch( event->getTypeName(), event );

};

};
