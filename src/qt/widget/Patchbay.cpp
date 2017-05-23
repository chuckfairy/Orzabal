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

    connect(
        _UI.pushButton,
        SIGNAL( clicked() ),
        this,
        SLOT( handleAddClick() )
   );

};

void Patchbay::handleAddClick() {

    std::cout << "ADD CLICK\n";

};

void Patchbay::handleRemoveClick( bool checked ) {

};

} } };
