/**
 * Effects plugin dropdown
 */

#include "EffectDropdown.h"


namespace Orza { namespace App { namespace Widget {


EffectDropdown::EffectDropdown( Jack::Server * s ) :
    AbstractPluginDropdown( s )
{

    //connect( this, SIGNAL( currentIndexChanged( int ) ), this, SLOT( handleSelectionChanged( int ) ) );

    addPlugin( &_placeholder );

    LV2::Host * host = _Server->getPatchbay();

    vector<Audio::Plugin*> plugins = host->getSearch()->findAll();

    vector<Audio::Plugin*>::iterator it;

    for( it = plugins.begin(); it != plugins.end(); ++it ) {

        LV2::Plugin * p = (LV2::Plugin*) (*it);

        InstrumentOption opt = {
            p->getName(),
            p->getURI()
        };

        addPlugin( &opt );

    }

};

} } };
