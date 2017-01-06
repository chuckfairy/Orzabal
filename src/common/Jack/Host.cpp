/**
 * Jack audio mod
 *
 */
#include <vector>
#include <iostream>
#include <string>


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
 */

Host::Host() {};


/**
 * Create with jack
 *
 */

Host::Host( jack_client_t * j ) {

    setJackClient( j );

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

};


/**
 * Host back connection to private client
 *
 */

int Host::connectJackPort( const char * source, const char * destination ) {

    return jack_connect( _jackClient, source, destination );

};


/**
 * Connection to mono
 */

bool Host::connectInputTo( const char * out ) {

    connectJackPort( _inputLeftName, out );
    connectJackPort( _inputRightName, out );

    return true;

};


/**
 * Connection to stereo
 */

bool Host::connectInputTo( const char * outLeft, const char * outRight ) {

    connectJackPort( _inputLeftName, outLeft );
    connectJackPort( _inputRightName, outRight );

    return true;

};


/**
 * Connection to mono
 */

bool Host::connectOutputTo( const char * input ) {

    connectJackPort( getPortFullName( _outputLeftName ), input );
    connectJackPort( getPortFullName( _outputRightName ), input );

    return true;

};


/**
 * Connection to stereo
 */

bool Host::connectOutputTo( const char * inLeft, const char * inRight ) {

    connectJackPort( getPortFullName( _outputLeftName ), inLeft );
    connectJackPort( getPortFullName( _outputRightName ), inRight );

    return true;

};


/**
 * Connect input output redirect
 */

void Host::connectRedirect() {

    connectJackPort(
        getPortFullName( _outputLeftName ),
        getPortFullName( _inputLeftName )
    );

    connectJackPort(
        getPortFullName( _outputRightName ),
        getPortFullName( _inputRightName )
    );

};


/**
 * Get global jack ports
 *
 */

vector<Port> Host::getPortsByType( enum JackPortFlags PORT_FLAG ) {

    vector<Port> ports;

    const char ** globalPorts = jack_get_ports(
        _jackClient,
        0,
        JACK_DEFAULT_AUDIO_TYPE,
        PORT_FLAG
    );

    int iClientPort = 0;

    while( globalPorts[iClientPort] ) {

        string clientName( globalPorts[iClientPort] );

        Port p {
            globalPorts[iClientPort]
        };

        ports.push_back( p );

        int *pClient = 0;
        int *pPort   = 0;
        jack_port_t *pHostPort = jack_port_by_name(_jackClient, clientName.c_str() );
        int iColon = clientName.find(':');

        if (pHostPort && iColon >= 0) {

            //QString sClientName = left
            //QString sPortName   = right
            //pClient = static_cast<qjackctlHostClient *> (findClient(sClientName));

            //if (pClient)
            //pPort = static_cast<qjackctlHostPort *> (pClient->findPort(sPortName));

            if (pClient == 0) {

                //pClient->setClientName(sClientName);

            }

            //if (pClient && pPort == 0) {

            //pPort = new qjackctlHostPort(pClient, pHostPort);
            //pPort->setPortName(sPortName);
            //iDirtyCount++;

            //}

            //if (pPort)
            //pPort->markClientPort(1);

        }

        iClientPort++;

    }

    return ports;

};


/**
 * Get ports by input type HostPortIsInput
 */

vector<Port> Host::getInputPorts() {

    return getPortsByType( JackPortIsInput );

};


/**
 * Get ports by input type JackPortIsOutput
 */

vector<Port> Host::getOutputPorts() {

    return getPortsByType( JackPortIsOutput );

};

};
