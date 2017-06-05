/**
 * Patchbay tab UI impl
 */
#include <MainWindow.h>

#include "PatchbayPlugin.h"
#include "Patchbay.h"


namespace Orza { namespace App { namespace Widget {

Patchbay::Patchbay( MainWindow * app ) :
    _App( app ),
    _WidgetContent( new QWidget() ),
    _LayoutWidget( new QWidget() ),
    _Dropdown( new EffectDropdown( app->getServer() ) )
{

    _UI.setupUi( _WidgetContent );

    _UI.horizontalLayout->insertWidget( 0, _Dropdown );

    app->getUI()->tabWidget->insertTab( 1, _WidgetContent, "Effects" );

    _Layout = new QGridLayout;

    _LayoutWidget->setLayout( _Layout );

    _UI.scrollArea->setWidget( _LayoutWidget );

    connect(
        _UI.pushButton,
        SIGNAL( clicked() ),
        this,
        SLOT( handleAddClick() )
   );

};


/**
 * Add click handle and add plugin
 */

void Patchbay::handleAddClick() {

    std::cout << "ADD CLICK\n";

    int index = _Dropdown->currentIndex();

    if ( index == 0 ) { return; }


    //Create patchbay plugin ui

    LV2::Host * h = _App->getServer()->getPatchbay();
    Audio::Plugin * p = _Dropdown->getCurrentPlugin();

    PatchbayPlugin * plugin = new PatchbayPlugin( p );

    _plugins.push_back( plugin );

    _Layout->addWidget( plugin->getWidget() );

};

void Patchbay::handleRemoveClick( bool checked ) {

};

} } };
