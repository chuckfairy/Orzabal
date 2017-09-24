/**
 * Effects plugin dropdown
 */
#include <Audio/Plugin.h>

#include "EffectDropdown.h"

using Orza::PluginSearch::LoadedPlugins;


namespace Orza { namespace App { namespace Widget {


EffectDropdown::EffectDropdown( LoadedPlugins * plugins ) :
    AbstractPluginDropdown()
{

    //connect( this, SIGNAL( currentIndexChanged( int ) ), this, SLOT( handleSelectionChanged( int ) ) );

    _plugins = plugins->getAudioEffects();

    vector<Audio::Plugin*>::iterator it;

    for( it = _plugins.begin(); it != _plugins.end(); ++it ) {

        Audio::Plugin * p = (Audio::Plugin*) (*it);

        InstrumentOption opt = {
            p->getName(),
            p->getID()
        };

        addPlugin( &opt );

    }

};

} } };
