/**
 * Patchbay tab UI impl
 */
#include <MainWindow.h>

#include "Patchbay.h"

#include "InstrumentDropdown.h"


namespace Orza { namespace App { namespace Widget {

Patchbay::Patchbay( MainWindow * app ) :
    _App( app ),
    _WidgetContent( new QWidget() )
{

    _UI.setupUi( _WidgetContent );

    _UI.horizontalLayout->insertWidget( 0, new InstrumentDropdown( _App->getServer() ) );

    int index = app->getUI()->tabWidget->addTab( _WidgetContent, "Effects" );

};

void Patchbay::handleAddClick( int index ) {

};

void Patchbay::handleRemoveClick( int index ) {

    std::cout << index;

};

} } };
