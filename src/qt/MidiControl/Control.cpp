/**
 * Control widget editor
 */
#include "Control.h"

namespace Orza { namespace App { namespace MidiControl {

/**
 * Forwarding
 */


/**
 * Main class
 */

Control::Control( MainWindow * app ) :
    _App( app ),
    _WidgetContent( new QWidget() )
{

    _Tab.setupUi( _WidgetContent );

    int index = app->getUI()->tabWidget->addTab( _WidgetContent, "Control" );


    //Events

    connect( _Tab.add_btn, SIGNAL( clicked() ), this, SLOT( addControlPort() ) );

};


/**
 * Add port
 */

void Control::addControlPort() {

};

} } };

