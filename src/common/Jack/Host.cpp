/**
 * Jack audio mod
 *
 */
#include <string>
#include <vector>
#include <iostream>

#include <jack/types.h>

#include "Events/RedirectionEvent.h"
#include "Events/UpdateEvent.h"
#include "Events/LatencyEvent.h"
#include "Events/BufferEvent.h"

#include "Server.h"
#include "Host.h"


using std::string;
using std::vector;


/**
 * Midi Alsa extended class
 *
 */

namespace Jack {


/**
 * Constructs
 * Create with jack or server
 *
 */

Host::Host( jack_client_t * j ) :
    ServerStandalone( j )
{
};


Host::Host( Server * s ) :
    ServerStandalone( s->getJackClient() ),
    _Server( s )
{
};


/**
 *
 */

void Host::start() {

};


/**
 * Host register and create ports
 *
 */

void Host::createPorts() {

    _inputLeft = jack_port_register(
        _jackClient,
        _inputLeftName,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsInput,
        0
    );

    _inputRight = jack_port_register(
        _jackClient,
        _inputRightName,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsInput,
        0
    );

    _outputLeft = jack_port_register(
        _jackClient,
        _outputLeftName,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsOutput,
        0
    );

    _outputRight = jack_port_register(
        _jackClient,
        _outputRightName,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsOutput,
        0
    );

    _inputPorts.push_back( _inputLeft );
    _inputPorts.push_back( _inputRight );
    _outputPorts.push_back( _outputLeft );
    _outputPorts.push_back( _outputRight );

};



/**
 * Interal port checker
 */

bool Host::isInternalPort( const char * name ) {

    const char * clientName =  jack_get_client_name( _jackClient );

    return (
        strncmp( clientName, name,  strlen( clientName ) ) == 0
    );

};


/**
 * Host back connection to private client
 *
 */

int Host::connectJackPort( const char * source, const char * destination ) {

    return jack_connect( _jackClient, source, destination );

};


/**
 * Host back connection to private client
 *
 */

int Host::disconnectJackPort( jack_port_t * port ) {

    return jack_port_disconnect( _jackClient, port );

};

/**
 * Connection to mono
 */

bool Host::connectInputTo( const char * out ) {

    connectJackPort( out, getPortFullName( _inputLeftName ) );
    connectJackPort( out, getPortFullName( _inputRightName ) );

    return true;

};


/**
 * Connection to stereo
 */

bool Host::connectInputTo( const char * outLeft, const char * outRight ) {

    std::cout << "\n" << outLeft << " " << outRight << "\n";

    connectJackPort( outLeft, getPortFullName( _inputLeftName ) );
    connectJackPort( outRight, getPortFullName( _inputRightName ) );

    return true;

};


/**
 * Connection to mono
 */

bool Host::connectOutputTo( const char * input ) {

    connectJackPort( getPortFullName( _outputLeftName ), input );
    connectJackPort( getPortFullName( _outputRightName ), input );

    _lastOutputLeft = new string( input );
    _lastOutputRight = new string( input );

    return true;

};


/**
 * Connection to stereo
 */

bool Host::connectOutputTo( const char * inLeft, const char * inRight ) {

    connectJackPort( getPortFullName( _outputLeftName ), inLeft );
    connectJackPort( getPortFullName( _outputRightName ), inRight );

    _lastOutputLeft = new string( inLeft );
    _lastOutputRight = new string( inRight );

    return true;

};


/**
 * Disconnections
 */

void Host::disconnectInputs() {

    disconnectJackPort( _inputLeft );
    disconnectJackPort( _inputRight );

};

void Host::disconnectOutputs() {

    jack_disconnect(
        _jackClient,
        getPortFullName( _outputLeftName ),
        _lastOutputLeft->c_str()
    );

    jack_disconnect(
        _jackClient,
        getPortFullName( _outputRightName ),
        _lastOutputRight->c_str()
    );

};


/**
 * Get global jack ports
 *
 */

vector<Port> Host::getPortsByType(
    enum JackPortFlags PORT_FLAG,
    const char * AUDIO_TYPE
) {

    vector<Port> ports;

    const char ** globalPorts = jack_get_ports(
        _jackClient,
        0,
        AUDIO_TYPE,
        PORT_FLAG
    );

    int iClientPort = 0;

    while( globalPorts[iClientPort] ) {

        //std::cout << ;

        const char * portName = globalPorts[ iClientPort ];


        //Check if interal

        if( isInternalPort( portName ) ) {

            ++iClientPort;

            continue;

        }


        string clientName( portName );

        Port p;

        p.nameString = portName;
        p.name = portName;
        p.jack_port = jack_port_by_name(_jackClient, portName );

        ports.push_back( p );

        int *pClient = 0;
        int *pPort   = 0;
        int iColon = clientName.find(':');

        if( p.jack_port && iColon >= 0 ) {

            //QString sClientName = left
            //QString sPortName   = right
            //pClient = static_cast<qjackctlHostClient *> (findClient(sClientName));

            //if (pClient)
            //pPort = static_cast<qjackctlHostPort *> (pClient->findPort(sPortName));

            if (pClient == 0) {

                //pClient->setClientName(sClientName);

            }

        }

        ++iClientPort;

    }

    return ports;

};


/**
 * Get ports by input type HostPortIsInput
 */

vector<Port> Host::getInputPorts() {

    return getPortsByType( JackPortIsInput, JACK_DEFAULT_AUDIO_TYPE );

};


/**
 * Get ports by input type JackPortIsOutput
 */

vector<Port> Host::getOutputPorts() {

    return getPortsByType( JackPortIsOutput, JACK_DEFAULT_AUDIO_TYPE );

};


/**
 * Redirection of input to out
 */

void Host::redirectInput( jack_nframes_t nframes ) {

    jack_default_audio_sample_t
        * inLeft,
        * inRight,
        * outLeft,
        * outRight;

    size_t bufSize = sizeof( jack_default_audio_sample_t ) * (nframes);


    //Port buffer getting

    inLeft = (jack_default_audio_sample_t*)
        jack_port_get_buffer( _inputLeft, nframes );

    inRight = (jack_default_audio_sample_t*)
        jack_port_get_buffer( _inputRight, nframes);

    outLeft = (jack_default_audio_sample_t*)
        jack_port_get_buffer( _outputLeft, nframes );

    outRight = (jack_default_audio_sample_t*)
        jack_port_get_buffer( _outputRight, nframes );


    //Buffer copy redirection

    memcpy( outLeft, inLeft, bufSize );
    memcpy( outRight, inRight, bufSize );

};


/**
 * Server callback processing mainly redirection
 * Will use Orzabal server or standalone use
 *
 */

void Host::setServerCallbacks() {

    if( ! _Server ) {

        throw std::runtime_error( "No server set" );

    }


    Util::Event * updateEv = (Util::Event*) new RedirectionEvent( this );

    _Server->on( Jack::Server::UPDATE_EVENT, updateEv );

};

};
