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

    connectEffectPorts();

    setServerCallbacks();

};


/**
 * Main audio add
 */

void PatchbayEffects::addEffect( Audio::Plugin * p ) {

    p->start();

    p->run();

    _ActiveEffects.push_back( p );

    connectEffectPorts();

};


/**
 * Audio effects connection
 */

void PatchbayEffects::connectEffectPorts() {

    //Disconnect redirector

    vector<jack_port_t*> * patchbayOutInputs = _Output->getInputPorts();

    disconnectJackPort( _outputLeft );
    disconnectJackPort( _outputRight );

    disconnectJackPort(  patchbayOutInputs->at( 0 ) );
    disconnectJackPort( patchbayOutInputs->at( 1 ) );


    //If empty just redirect to output

    if ( _ActiveEffects.empty() ) {

        connectOutputTo(
           _Output->getInputNameLeft(),
           _Output->getInputNameRight()
        );

        return;

    }


    //Connect chain

    disconnectEffectPorts();

    vector<Audio::Plugin*>::iterator it;

    for( it = _ActiveEffects.begin(); it != _ActiveEffects.end(); ++ it ) {

        Plugin * p = (Plugin*) (*it);

        if( ! p->isActive() ) { continue; }


        //Get ports

        vector<jack_port_t*> inputs = p->getInputJackPorts();
        vector<jack_port_t*> outputs = p->getOutputJackPorts();


        //First one connect to internal out

        if( (*it) == _ActiveEffects.front() ) {

            connectOutputTo(
                jack_port_name( inputs[0] ),
                jack_port_name( inputs[1] )
            );

        }


        //Send to output or next plugin

        if( (*it) == _ActiveEffects.back() ) {

            _Output->connectInputTo(
                jack_port_name( outputs[0] ),
                jack_port_name( outputs[1] )
            );

        } else {

            Plugin * nextPlugin = (Plugin*) (*(it + 1));

            vector<jack_port_t*> nextInputs = nextPlugin->getInputJackPorts();

            connectJackPort(
                jack_port_name( outputs[0] ),
                jack_port_name( nextInputs[0] )
            );

            connectJackPort(
                jack_port_name( outputs[1] ),
                jack_port_name( nextInputs[1] )
            );

        }

    }

};


/**
 * Jack port disconnector plugins
 */

void PatchbayEffects::disconnectEffectPorts() {

    //Connect chain

    vector<Audio::Plugin*>::iterator it;

    for( it = _ActiveEffects.begin(); it != _ActiveEffects.end(); ++ it ) {

        Plugin * p = (Plugin*) (*it);

        if( ! p->isActive() ) { continue; }


        //Get ports and disconnect

        vector<jack_port_t*> inputs = p->getInputJackPorts();
        vector<jack_port_t*> outputs = p->getOutputJackPorts();

        disconnectJackPort( inputs[0] );
        disconnectJackPort( inputs[1] );
        disconnectJackPort( outputs[0] );
        disconnectJackPort( outputs[1] );

    }

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
 * main update method
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

};

};
