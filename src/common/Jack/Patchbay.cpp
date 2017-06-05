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

Patchbay::Patchbay( jack_client_t * c ) :
    ServerStandalone( c )
{
};


/**
 * Server related
 */

void Patchbay::setServer( Server * s ) {

    _Server = s;

};


/**
 * Plugin starting
 */

void Patchbay::addPlugin( Audio::Plugin * p ) {

    _ActivePlugins.push_back( p );

    p->start();

    connectPluginPorts( p );

    p->run();

};


/**
 * Remove active plugin
 */

void Patchbay::removePlugin( uint32_t index ) {

    if( ! _ActivePlugins[ index ] ) { return; }

    Audio::Plugin * p = _ActivePlugins[ index ];

    _ActivePlugins.erase( _ActivePlugins.begin() + index );

    p->stop();

};


/**
 * Clear all plugins
 */

void Patchbay::clearPlugins() {

    if( _ActivePlugins.empty() ) { return; }

    while( ! _ActivePlugins.empty() ) {

        removePlugin( 0 );

    }

}



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

        audio->connectInputTo(
            jack_port_name( portLeft->jack_port ),
            jack_port_name( portRight->jack_port )
        );

    } else {

        Jack::Port * portMono = (Jack::Port*) p->getPort(
            (*ports)[ 0 ]
        );

        audio->connectInputTo(
            jack_port_name( portMono->jack_port )
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


/**
 * Audio effects connection
 */

void Patchbay::connectAudioEffectPorts( Audio::Plugin * plugin ) {

    Jack::Host * audio = _Server->getAudio();


    //Connect last effect chain

    if( ! _ActiveEffects.empty() ) {

        connectAudioEffectLastPort( plugin );

    }


    //New plugins inputs

    vector<long> * inputs = plugin->getInputPorts();

    if( inputs->size() > 1 ) {

        Jack::Port * portLeft = (Jack::Port*) plugin->getPort(
            (*inputs)[ 0 ]
        );

        Jack::Port * portRight = (Jack::Port*) plugin->getPort(
            (*inputs)[ 1 ]
        );

    } else {

        Jack::Port * portMono = (Jack::Port*) plugin->getPort(
            (*inputs)[ 0 ]
        );

    }

    _ActiveEffects.push_back( plugin );

};


/**
 * Connect last audio effect and connect to new plugin
 * Will disconnect from last
 */

void Patchbay::connectAudioEffectLastPort( Audio::Plugin * plugin ) {

    Jack::Host * audio = _Server->getAudio();

    Audio::Plugin * lastEffect = _ActiveEffects.back();


    //Disconnect last effect

    vector<long> * outputs = lastEffect->getOutputPorts();

    vector<long>::iterator it;

    for( it = outputs->begin(); it != outputs->end(); ++ it )  {

        Port * port = (Port*) plugin->getPort( (*it) );

        audio->disconnectJackPort( port->jack_port );

    }


    //Get ports to connect

    Jack::Port * effectOutputs[2];
    Jack::Port * effectInputs[2];


    //Last plugins outputs

    if( outputs->size() > 1 ) {

        Jack::Port * portLeft = (Jack::Port*) lastEffect->getPort(
            (*outputs)[ 0 ]
        );

        Jack::Port * portRight = (Jack::Port*) lastEffect->getPort(
            (*outputs)[ 1 ]
        );

        effectOutputs[0] =  portLeft;
        effectOutputs[1] = portRight;

    } else {

        Jack::Port * portMono = (Jack::Port*) lastEffect->getPort(
            (*outputs)[ 0 ]
        );

        effectOutputs[0] =  portMono;
        effectOutputs[1] =  portMono;

    }


    //New plugins inputs

    vector<long> * inputs = plugin->getInputPorts();

    if( inputs->size() > 1 ) {

        Jack::Port * portLeft = (Jack::Port*) plugin->getPort(
            (*inputs)[ 0 ]
        );

        Jack::Port * portRight = (Jack::Port*) plugin->getPort(
            (*inputs)[ 1 ]
        );

        effectInputs[0] =  portLeft;
        effectInputs[1] = portRight;

    } else {

        Jack::Port * portMono = (Jack::Port*) plugin->getPort(
            (*inputs)[ 0 ]
        );

        effectInputs[0] =  portMono;
        effectInputs[1] =  portMono;

    }


    //Connect via audio api

    audio->connectJackPort(
        jack_port_name( effectOutputs[ 0 ]->jack_port ),
        jack_port_name( effectInputs[ 0 ]->jack_port )
    );

    audio->connectJackPort(
        jack_port_name( effectOutputs[ 1 ]->jack_port ),
        jack_port_name( effectInputs[ 1 ]->jack_port )
    );

}

};
