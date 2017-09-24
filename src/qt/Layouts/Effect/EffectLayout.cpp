/**
 * Effect layout impl
 */
#include <MainWindow.h>

#include "EffectLayout.h"

using Orza::App::Widget::Patchbay;

namespace Orza { namespace App { namespace Layouts {

/**
 * Construct
 */

EffectLayout::EffectLayout( MainWindow * app ) :
    _App( app ),
    _Patchbay( new Patchbay( app ) )
{

    _name = "effect";

};


/**
 * Main setup
 */

void EffectLayout::setup() {

    _App->getUI()
        ->tabWidget->insertTab( 0, _Patchbay->getWidgetContainer(), "Effects" );

    _App->getUI()->tabWidget->setCurrentIndex( 0 );

};


/**
 * @TODO
 */

void EffectLayout::takedown() {

    _App->getUI()
        ->tabWidget->removeTab( 0 );

};

}; }; };
