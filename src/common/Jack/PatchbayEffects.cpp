/**
 * Patchbay effects impl
 */
#include "Plugin.h"
#include "Server.h"
#include "PatchbayEffects.h"
#include "Events/RedirectionEventStereo.h"

namespace Jack {

/**
 * Construct from stereo interface
 */

PatchbayEffects::PatchbayEffects( Server * server ) :
    StereoHostInterface( server->getJackClient() ),
    _Server( server ),
    _Output( new PatchbayEffectsOutput( server->getJackClient() ) )
{

    createPorts();

    connectOutputTo(
       _Output->getInputNameLeft(),
       _Output->getInputNameRight()
    );

    setServerCallbacks();

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

    vector<long> lastInputs = plugin->getInputPortsStereo();

    Port * lastInputPortLeft = (Port*) plugin->getPort(
        lastInputs[ 0 ]
    );
    Port * lastInputPortRight = (Port*) plugin->getPort(
        lastInputs[ 1 ]
    );

    connectOutputTo(
        jack_port_name( lastInputPortLeft->jack_port ),
        jack_port_name( lastInputPortRight->jack_port )
    );


    vector<long> lastOutputs = plugin->getOutputPortsStereo();

    Port * lastOutputPortLeft = (Port*) plugin->getPort(
        lastOutputs[ 0 ]
    );
    Port * lastOutputPortRight = (Port*) plugin->getPort(
        lastOutputs[ 1 ]
    );

//    _Output->connectInputTo(
//        jack_port_name( lastOutputPortLeft->jack_port ),
//        jack_port_name( lastOutputPortRight->jack_port )
//    );

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
 * Update jack host from jack frame pointer
 */

void PatchbayEffects::updateJack( jack_nframes_t nframes ) {

    vector<Audio::Plugin*>::iterator it;

    for( it = _ActiveEffects.begin(); it != _ActiveEffects.end(); ++ it ) {

        Plugin * p = (Plugin*) (*it);

        if( p->isActive() ) {

            p->updateJack( nframes );

        }

    }

};


/**
 * Server callback processing mainly redirection
 * Will use Orzabal server or standalone use
 *
 */

void PatchbayEffects::setServerCallbacks() {

    Util::Event * e = new RedirectionEventStereo<PatchbayEffects>( this );

    _Server->on( Server::UPDATE_EVENT, e );

};


/**
 * Redirect to first effect input
 */

void PatchbayEffects::redirectInput( jack_nframes_t nframes ) {

    StereoHostInterface::redirectInput( nframes );

    //Redirect effects input to first effect
    //and last input to main output

    if( ! _ActiveEffects.empty() ) {

        redirectEffects( nframes );

    }

    _Output->redirectInput( nframes );

};


/**
 * Patchbay redirect of active effects output to other input
 */

void PatchbayEffects::redirectEffects( jack_nframes_t nframes ) {

    updateJack( nframes );


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


}

};
