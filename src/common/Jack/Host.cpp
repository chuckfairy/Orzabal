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

    setHostClient( j );

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

int Host::connectHostPort( const char * source, const char * destination ) {

    return jack_connect( _jackClient, source, destination );

};


/**
 * Connection to mono
 */

bool Host::connectInputTo( const char * out ) {

    connectHostPort( _inputLeftName, out );
    connectHostPort( _inputRightName, out );

    return true;

};


/**
 * Connection to stereo
 */

bool Host::connectInputTo( const char * outLeft, const char * outRight ) {

    connectHostPort( _inputLeftName, outLeft );
    connectHostPort( _inputRightName, outRight );

    return true;

};


/**
 * Connection to mono
 */

bool Host::connectOutputTo( const char * input ) {

    connectHostPort( getPortFullName( _outputLeftName ), input );
    connectHostPort( getPortFullName( _outputRightName ), input );

    return true;

};


/**
 * Connection to stereo
 */

bool Host::connectOutputTo( const char * inLeft, const char * inRight ) {

    connectHostPort( getPortFullName( _outputLeftName ), inLeft );
    connectHostPort( getPortFullName( _outputRightName ), inRight );

    return true;

};


/**
 * Connect input output redirect
 */

void Host::connectRedirect() {

    connectHostPort(
        getPortFullName( _outputLeftName ),
        getPortFullName( _inputLeftName )
    );

    connectHostPort(
        getPortFullName( _outputRightName ),
        getPortFullName( _inputRightName )
    );

};


/**
 * Get global jack ports
 *
 */

vector<Port> Host::getPortsByType( enum HostPortFlags PORT_FLAG ) {

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

    return getPortsByType( HostPortIsInput );

};


/**
 * Get ports by input type HostPortIsOutput
 */

vector<Port> Host::getOutputPorts() {

    return getPortsByType( HostPortIsOutput );

};

};
