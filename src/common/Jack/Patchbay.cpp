/**
 * Jack host impl
 *
 */
#include <jack/jack.h>

#include "Server.h"
#include "Patchbay.h"
#include "Midi.h"
#include "Port.h"


namespace Jack {


/**
 * Construct
 */

Patchbay::Patchbay( jack_client_t * c ) {

    setJackClient( c );

};


/**
 * Server related
 */

void Patchbay::setServer( Server * s ) {

    _Server = s;

};


/**
 * Plugin port connector to server audio
 */

void Patchbay::connectPluginPorts( Audio::Plugin * p ) {

    connectPluginAudioPorts( p );
    connectPluginMidiPorts( p );

};


/**
 * Audio outputs connector
 * @TODO support more than stereo
 *
 */

void Patchbay::connectPluginAudioPorts( Audio::Plugin * p ) {

    //Get outputs

    vector<long> * ports = p->getOutputPorts();

    if( ports->empty() ) { return; }


    Jack::Host * audio = _Server->getAudio();

    //Stereo check

    if( ports->size() > 1 ) {

        Jack::Port * portLeft = (Jack::Port*) p->getPort(
            (*ports)[ 0 ]
        );

        Jack::Port * portRight = (Jack::Port*) p->getPort(
            (*ports)[ 1 ]
        );

        const char * leftName = audio->getPortFullName( portLeft->name );

        audio->connectInputTo(
            jack_port_name( portLeft->jack_port ),
            audio->getPortFullName( portRight->name )
        );

    } else {

        Jack::Port * portMono = (Jack::Port*) p->getPort(
            (*ports)[ 0 ]
        );

        audio->connectInputTo(
            audio->getPortFullName( portMono->name )
        );

    }

};


/**
 * Midi connector for plugin
 */

void Patchbay::connectPluginMidiPorts( Audio::Plugin * p ) {

    vector<long> * ports = p->getMidiPorts();

    if( ports->empty() ) { return; }


    //Connect to all midi inputs

    Jack::Midi * midi = _Server->getMidi();

    vector<long>::iterator it;

    for( it = ports->begin(); it != ports->end(); ++ it ) {

        Port * port = (Port*) p->getPort( *it );

        if( ! port->jack_port ) { continue; }

        if( port->flow == Audio::FLOW_INPUT ) {

            midi->addInput( port->jack_port );

        }

    }

};

};
