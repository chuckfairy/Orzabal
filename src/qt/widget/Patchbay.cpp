/**
 * Patchbay tab UI impl
 */
#include <MainWindow.h>

#include "PatchbayPlugin.h"
#include "Patchbay.h"

#include "InstrumentDropdown.h"


namespace Orza { namespace App { namespace Widget {

Patchbay::Patchbay( MainWindow * app ) :
    _App( app ),
    _WidgetContent( new QWidget() ),
    _LayoutWidget( new QWidget() )
{

    _UI.setupUi( _WidgetContent );

    _UI.horizontalLayout->insertWidget( 0, new InstrumentDropdown( _App->getServer() ) );

    int index = app->getUI()->tabWidget->addTab( _WidgetContent, "Effects" );

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

    PatchbayPlugin * plugin = new PatchbayPlugin();

    _plugins.push_back( plugin );

    _Layout->addWidget( plugin->getWidget() );

};

void Patchbay::handleRemoveClick( bool checked ) {

};

} } };
