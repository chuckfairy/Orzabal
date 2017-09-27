/**
 * Effect layout impl
 */
#include <MainWindow.h>

#include "EffectLayout.h"

#include <Jack/PatchbayEffects.h>
#include <Settings/Layout.h>


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


    //Connect default first input

    vector<Jack::Port> outputs = _App->getServer()->getAudio()->getOutputPorts();

    if( ! outputs.empty() ) {

        _App->getServer()->getPatchbay()->getEffects()->connectInputTo(
            outputs[0].name
        );

        _App->getSettingsLayout()->getInputDropdown()->setCurrentIndex( 1 );

    }

};


/**
 * @TODO
 */

void EffectLayout::takedown() {

    _App->getUI()
        ->tabWidget->removeTab( 0 );

};

}; }; };
