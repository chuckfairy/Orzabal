/**
 * Effects plugin dropdown
 */

#include "EffectDropdown.h"


namespace Orza { namespace App { namespace Widget {


EffectDropdown::EffectDropdown( Jack::Server * s ) :
    AbstractPluginDropdown( s )
{

    //connect( this, SIGNAL( currentIndexChanged( int ) ), this, SLOT( handleSelectionChanged( int ) ) );

    LV2::Host * host = _Server->getPatchbay();

    _plugins = host->getSearch()->findAudioEffects();

    vector<Audio::Plugin*>::iterator it;

    for( it = _plugins.begin(); it != _plugins.end(); ++it ) {

        LV2::Plugin * p = (LV2::Plugin*) (*it);

        InstrumentOption opt = {
            p->getName(),
            p->getURI()
        };

        addPlugin( &opt );

    }

};

} } };
