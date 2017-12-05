/**
 * Control widget editor
 */
#include <Jack/Midi.h>

#include <MainWindow.h>

#include "ControlPort.h"

#include "Control.h"

using Jack::MidiControlPort;


namespace Orza { namespace App { namespace MidiControl {


/**
 * Main class
 */

Control::Control( MainWindow * app ) :
    _App( app ),
    _WidgetContent( new QWidget() )
{

    _UI.setupUi( _WidgetContent );

    int index = app->getUI()->tabWidget->addTab( _WidgetContent, "Control" );


    //Events

    connect( _UI.add_btn, SIGNAL( clicked() ), this, SLOT( addControlPort() ) );

    updateDropdown();

};


/**
 * Add port
 */

void Control::addControlPort() {

    Jack::MidiControlPort * port = _Ports[ _UI.control_dropdown->currentIndex() ];

    ControlPort * uiPort = new ControlPort( _App, port );

    _UI.scroll_layout->addWidget( uiPort );


    //set events

    addNode( uiPort );

};


/**
 * update midi port controls
 */

void Control::updateDropdown() {

    _Ports = _App->getServer()
        ->getMidi()->getMidiControlPorts();

    vector<MidiControlPort*>::iterator it;

    for( it = _Ports.begin(); it != _Ports.end(); ++ it ) {

        _UI.control_dropdown->addItem( (*it)->getName() );

    }

};

} } };
