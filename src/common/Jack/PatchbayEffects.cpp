/**
 * Patchbay effects impl
 */
#include <Util/Vector.h>
#include <Audio/Plugin.h>

#include "Plugin.h"
#include "Server.h"
#include "PatchbayEffects.h"
#include "PluginRepository.h"
#include "Events/RedirectionEventStereo.h"

namespace Jack {

/**
 * Construct from stereo interface
 */

PatchbayEffects::PatchbayEffects( Server * server ) :
    StereoHostInterface( server->getJackClient() ),
    _Server( server ),
    _Output( new PatchbayEffectsOutput( server->getJackClient() ) ),
    _Repo( new PluginRepository )
{

    createPorts();

    connectEffectPorts();

};


/**
 * Main audio add
 */

void PatchbayEffects::addEffect( Audio::Plugin * p ) {

    setActive( false );

    p->start();

    p->run();

    _Repo->add( (Plugin*) p );

    setActive( true );

    connectEffectPorts();

};


/**
 * Remove effect and stop
 */

void PatchbayEffects::removeEffect( Audio::Plugin * p ) {

    _Repo->remove( (Plugin*) p );

    p->stop();

    connectEffectPorts();

};


/**
 * Pause plugin keep in repo
 */

void PatchbayEffects::pauseEffect( Audio::Plugin * p ) {

    p->pause();

    connectEffectPorts();

};

/**
 * Get control ports of active plugins
 */

vector<Audio::Port*> PatchbayEffects::getControlPorts() {

    vector<Audio::Port*> ports;

    vector<Plugin*>::iterator it;

    vector<Plugin*> _ActiveEffects = _Repo->getAll();

    for( it = _ActiveEffects.begin(); it != _ActiveEffects.end(); ++ it ) {

        Audio::Plugin * p = (Audio::Plugin*) (*it);

        vector<Audio::Port*> pluginPorts = p->getPortsFromIndex( p->getControlPorts() );

        Util::Vector::append( &ports, pluginPorts );

    };

    return ports;

}


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

    if ( _Repo->empty() ) {

        connectOutputTo(
           _Output->getInputNameLeft(),
           _Output->getInputNameRight()
        );

        return;

    }


    //Disconnect all previous connections

    disconnectEffectPorts();


    //Connect chain

    vector<Plugin*> _ActiveEffects = _Repo->getAll();

    vector<Plugin*>::iterator it;

    bool isFirst = true;

    Plugin * lastPlugin = nullptr;

    for( it = _ActiveEffects.begin(); it != _ActiveEffects.end(); ++ it ) {

        Plugin * p = (Plugin*) (*it);

        if( ! p->isActive() ) { continue; }


        //Get ports

        vector<jack_port_t*> inputs = p->getInputJackPorts();
        vector<jack_port_t*> outputs = p->getOutputJackPorts();


        //First one connect to internal out

        if( isFirst ) {

            connectOutputTo(
                jack_port_name( inputs[0] ),
                jack_port_name( inputs[1] )
            );

            isFirst = false;

        } else {

            vector<jack_port_t*> lastOutputs = lastPlugin->getOutputJackPorts();

            connectJackPort(
                jack_port_name( lastOutputs[0] ),
                jack_port_name( inputs[0] )
            );

            connectJackPort(
                jack_port_name( lastOutputs[1] ),
                jack_port_name( inputs[1] )
            );

        }

        lastPlugin = p;

    }

    if( lastPlugin != nullptr ) {

        vector<jack_port_t*> outputs = lastPlugin->getOutputJackPorts();

        _Output->connectInputTo(
            jack_port_name( outputs[0] ),
            jack_port_name( outputs[1] )
        );

    } else {

        connectOutputTo(
           _Output->getInputNameLeft(),
           _Output->getInputNameRight()
        );

    }

};


/**
 * Jack port disconnector plugins
 */

void PatchbayEffects::disconnectEffectPorts() {

    //Connect chain

    vector<Plugin*>::iterator it;

    vector<Plugin*> _ActiveEffects = _Repo->getAll();

    for( it = _ActiveEffects.begin(); it != _ActiveEffects.end(); ++ it ) {

        Plugin * p = (*it);

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

    if( ! isActive() ) { return; }

    vector<Plugin*>::iterator it;

    vector<Plugin*> _ActiveEffects = _Repo->getAll();

    for( it = _ActiveEffects.begin(); it != _ActiveEffects.end(); ++ it ) {

        Plugin * p = (Plugin*) (*it);

        if( p->isActive() ) {

            p->updateJack( nframes );

        }

    }

};


/**
 * Update jack host from jack frame pointer
 */

void PatchbayEffects::updateJackBufferSize( jack_nframes_t frames ) {

    vector<Plugin*>::iterator it;

    vector<Plugin*> effects = _Repo->getAll();

    for( it = effects.begin(); it != effects.end(); ++ it ) {

        Plugin * p = (*it);

        if( p->isActive() ) {

            p->updateJackBufferSize( frames );

        }

    }

};


/**
 * Update jack latency host for plugin jack ports
 */

void PatchbayEffects::updateJackLatency( jack_latency_callback_mode_t mode ) {

    vector<Plugin*>::iterator it;

    vector<Plugin*> effects = _Repo->getAll();

    for( it = effects.begin(); it != effects.end(); ++ it ) {

        Plugin * p = (*it);

        if( p->isActive() ) {

            p->updateJackLatency( mode );

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

    if( ! _Repo->empty() ) {

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
