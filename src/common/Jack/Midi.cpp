/**
 * Jack midi host
 */
#include "Midi.h"
#include "Server.h"


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



/**
 * Get ports by input type JackPortIsOutput
 */

vector<Port> Midi::getMidiPorts() {

    return getPortsByType( JackPortIsOutput, JACK_DEFAULT_MIDI_TYPE );

};

/**
 * Main port adders
 */

void Midi::addInput( const jack_port_t * port ) {

    _inputPorts.push_back( port );

    vector<const jack_port_t*>::iterator it;

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

void Midi::addOutput( const jack_port_t * port ) {

    _outputPorts.push_back( port );

    vector<const jack_port_t*>::iterator it;

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

    addOutput( ports[1].jack_port );

};

};
