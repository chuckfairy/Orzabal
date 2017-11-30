/**
 * Control widget editor
 */
#include <Jack/Midi.h>

#include <MainWindow.h>

#include <Widget/Events/RemoveClickEvent.h>

#include "ControlPort.h"

#include "Control.h"

using Jack::MidiControlPort;

using Orza::App::Widget::RemoveClickEvent;


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

    _UIPorts.add( uiPort );


    //set events

    Util::Event * e = new RemoveClickEvent<Control, ControlPort>( this );

    uiPort->on( Widget::TreeNode::DELETE_EVENT, e );

};


void Control::handleRemoveClick( ControlPort * port ) {

    _UIPorts.remove( port );

    delete port;

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
