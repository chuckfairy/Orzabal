/**
 * Patchbay effects impl
 */

#include "Server.h"
#include "PatchbayEffects.h"
#include "Events/RedirectionEventStereo.h"

namespace Jack {

/**
 * Construct from stereo interface
 */

PatchbayEffects::PatchbayEffects( Server * server ) :
    StereoHostInterface( server->getJackClient() ),
    _Server( server )
{

    createPorts();

};


/**
 * Audio effects connection
 */

void PatchbayEffects::connectEffectPorts( Audio::Plugin * plugin ) {

    //Connect last effect chain

    if( ! _ActiveEffects.empty() ) {

        connectEffectLastPort( plugin );

    }

    Jack::Host * audio = _Server->getAudio();


    //New plugins inputs

    vector<long> outputs = plugin->getInputPortsStereo();

    Jack::Port * portLeft = (Jack::Port*) plugin->getPort(
        outputs[ 0 ]
    );

    Jack::Port * portRight = (Jack::Port*) plugin->getPort(
        outputs[ 1 ]
    );

    audio->connectJackPort(
        jack_port_name( portLeft->jack_port ),
        jack_port_name( _inputLeft )
    );

    audio->connectJackPort(
        jack_port_name( portRight->jack_port ),
        jack_port_name( _outputRight )
    );

    _ActiveEffects.push_back( plugin );

};


/**
 * Server callback processing mainly redirection
 * Will use Orzabal server or standalone use
 *
 */

void PatchbayEffects::setServerCallbacks() {

    Util::Event * e = new RedirectionEventStereo( this );


    //Check on Server instance

    Util::Dispatcher * dispatch = ( _Server == NULL )
        ? (Util::Dispatcher*) this
        : (Util::Dispatcher*) _Server;


    //Setting

    dispatch->on( Server::UPDATE_EVENT, e );

};


/**
 * Connect last audio effect and connect to new plugin
 * Will disconnect from last
 */

void PatchbayEffects::connectEffectLastPort( Audio::Plugin * plugin ) {

    Jack::Host * audio = _Server->getAudio();

    Audio::Plugin * lastEffect = _ActiveEffects.back();


    //Disconnect last effect

    vector<long> outputs = lastEffect->getOutputPortsStereo();

    vector<long>::iterator it;

    for( it = outputs.begin(); it != outputs.end(); ++ it )  {

        Port * port = (Port*) plugin->getPort( (*it) );

        audio->disconnectJackPort( port->jack_port );

    }


    //Get ports to connect

    vector<long> effectInputs = plugin->getInputPortsStereo();

    Port * effectInputPortLeft = (Port*) plugin->getPort(
        effectInputs[ 0 ]
    );
    Port * effectInputPortRight = (Port*) plugin->getPort(
        effectInputs[ 1 ]
    );

    //Last effect outputs

    vector<long> lastOutputs = lastEffect->getOutputPortsStereo();

    Port * lastOutputPortLeft = (Port*) lastEffect->getPort(
        lastOutputs[ 0 ]
    );
    Port * lastOutputPortRight = (Port*) lastEffect->getPort(
        lastOutputs[ 1 ]
    );


    //Connect via audio api

    audio->connectJackPort(
        jack_port_name( lastOutputPortLeft->jack_port ),
        jack_port_name( effectInputPortLeft->jack_port )
    );

    audio->connectJackPort(
        jack_port_name( lastOutputPortRight->jack_port ),
        jack_port_name( effectInputPortRight->jack_port )
    );

};

};
