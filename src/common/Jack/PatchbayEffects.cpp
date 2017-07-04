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
 * Main audio add
 */

void PatchbayEffects::addEffect( Audio::Plugin * p ) {

    p->start();

    connectEffectPorts( p );

    _ActiveEffects.push_back( p );

    p->run();

};


/**
 * Audio effects connection
 */

void PatchbayEffects::connectEffectPorts( Audio::Plugin * plugin ) {

    //Connect last effect chain

    if ( ! _ActiveEffects.empty() ) {

        connectEffectLastPort( plugin );

    };

};


/**
 * Connect last audio effect and connect to new plugin
 * Will disconnect from last
 */

void PatchbayEffects::connectEffectLastPort( Audio::Plugin * plugin ) {

    //Use last effect

    Audio::Plugin * lastEffect = _ActiveEffects.back();


    //Disconnect last effect

    vector<long> outputs = lastEffect->getOutputPortsStereo();

    vector<long>::iterator it;

    for( it = outputs.begin(); it != outputs.end(); ++ it )  {

        Port * port = (Port*) plugin->getPort( (*it) );

        disconnectJackPort( port->jack_port );

    }


    //Get ports to connect

    vector<long> effectInputs = lastEffect->getInputPortsStereo();

    Port * effectInputPortLeft = (Port*) lastEffect->getPort(
        effectInputs[ 0 ]
    );
    Port * effectInputPortRight = (Port*) lastEffect->getPort(
        effectInputs[ 1 ]
    );

    //Last effect outputs

    vector<long> lastOutputs = plugin->getOutputPortsStereo();

    Port * lastOutputPortLeft = (Port*) plugin->getPort(
        lastOutputs[ 0 ]
    );
    Port * lastOutputPortRight = (Port*) plugin->getPort(
        lastOutputs[ 1 ]
    );


    //Connect via audio api

    connectJackPort(
        jack_port_name( lastOutputPortLeft->jack_port ),
        jack_port_name( effectInputPortLeft->jack_port )
    );

    connectJackPort(
        jack_port_name( lastOutputPortRight->jack_port ),
        jack_port_name( effectInputPortRight->jack_port )
    );

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
 * Redirect to first effect input
 */

void PatchbayEffects::redirectInput( jack_nframes_t nframes ) {

    if ( _ActiveEffects.empty() ) {

        StereoHostInterface::redirectInput( nframes );

        return;

    }


    //Redirect plugin effects

    Audio::Plugin * firstEffect = _ActiveEffects.front();
    Audio::Plugin * lastEffect = _ActiveEffects.back();


    //Get ports to connect

    vector<long> effectInputs = firstEffect->getInputPortsStereo();

    Port * effectInputPortLeft = (Port*) firstEffect->getPort(
        effectInputs[ 0 ]
    );
    Port * effectInputPortRight = (Port*) firstEffect->getPort(
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


    //Redirect effects input to first effect
    //and last input to main output

    redirectInputPort(
        _inputLeft,
        effectInputPortLeft->jack_port,
        nframes
    );

    redirectInputPort(
        _inputRight,
        effectInputPortRight->jack_port,
        nframes
    );

    redirectInputPort(
        lastOutputPortLeft->jack_port,
        _outputLeft,
        nframes
    );

    redirectInputPort(
        lastOutputPortRight->jack_port,
        _outputRight,
        nframes
    );

};

};
