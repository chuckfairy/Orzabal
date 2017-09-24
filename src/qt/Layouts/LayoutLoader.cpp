/**
 * Qt layout loader impl
 */
#include <Config/Defaults.h>

#include "Effect/EffectLayout.h"

#include "InstrumentEffect/InstrumentEffect.h"

#include <MainWindow.h>

#include "LayoutLoader.h"


namespace Orza { namespace App { namespace Layouts {


/**
 * Construct
 */

LayoutLoader::LayoutLoader( MainWindow * app ) :
    _App( app )
{

    //@TODO better

    Layout * defaultLayout;

    if( Config::DEFAULT_LAYOUT == "InstrumentEffect" ) {

        defaultLayout = new InstrumentEffect( _App );

    } else {

        defaultLayout = new EffectLayout( _App );

    }

    _Repo.add( defaultLayout );

    loadLayout( defaultLayout );

};


void LayoutLoader::loadLayout( Layout * l ) {

    l->setup();

    _CurrentLayout = l;

};


/**
 * Main layout load
 */

void LayoutLoader::load( json * setting ) {

    //if( setting["type"] ) {

        //throw std::runtime_error(
            //"no type in JSON"
        //);

    //}

};

}; }; };
