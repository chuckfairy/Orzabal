/**
 * ControlPort widget editor
 */
#include <Audio/Port.h>

#include <Jack/Patchbay.h>

#include <QMessageBox>

#include <MainWindow.h>

#include "ControlPort.h"


namespace Orza { namespace App { namespace MidiControl {


/**
 * Main class
 */

ControlPort::ControlPort( MainWindow * app, Jack::MidiControlPort * p ) :
    _App( app ),
    _ControlPort( p ),
    _WidgetContent( new QWidget() )
{

    _UI.setupUi( _WidgetContent );

    _UI.label->setText( _ControlPort->getName() );

    //Events

    connect( _UI.port_add_btn, SIGNAL( clicked() ), this, SLOT( addControlPortValue() ) );

    //connect( _UI.view_btn, SIGNAL( clicked() ), this, SLOT( toggleView() ) );
    //connect( _UI.delete_btn, SIGNAL( clicked() ), this, SLOT( remove() ) );

    updateDropdown();

};


/**
 * Add port
 */

void ControlPort::addControlPortValue() {

    //No plugins loaded

    if( _UI.port_add_dropdown->currentIndex() == -1 ) {

        QMessageBox Msgbox;
        Msgbox.setText( "No plugins loaded" );
        Msgbox.exec();

        return;

    }


    //load new control value

    Audio::Port * port = _ControlPorts[ _UI.port_add_dropdown->currentIndex() ];

};


/**
 * update midi port controls
 */

void ControlPort::updateDropdown() {

    _ControlPorts = _App->getServer()
        ->getPatchbay()->getControlPorts();

    vector<Audio::Port*>::iterator it;

    for( it = _ControlPorts.begin(); it != _ControlPorts.end(); ++ it ) {

        _UI.port_add_dropdown->addItem( (*it)->name );

    }

};

} } };

