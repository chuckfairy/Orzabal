/**
 * Patchbay effects impl
 */

#include "PatchbayEffects.h"

namespace Jack {

/**
 * Construct from stereo interface
 */

PatchbayEffects::PatchbayEffects( jack_client_t * client ) :
    StereoHostInterface( client )
{

};

/**
 * Audio effects connection
 */

void Patchbay::connectEffectPorts( Audio::Plugin * plugin ) {

    //Connect last effect chain

    if( ! _ActiveEffects.empty() ) {

        connectEffectLastPort( plugin );

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

void Patchbay::connectEffectLastPort( Audio::Plugin * plugin ) {

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

};

};
