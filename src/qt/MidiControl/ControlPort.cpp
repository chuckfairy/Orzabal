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

    Audio::PluginPortContainer * port = _PortContainers[
        _UI.port_add_dropdown->currentIndex()
    ];

    ControlPortValue * portValue = new ControlPortValue(
        _App->getServer()->getMidi(),
        _ControlPort,
        port
    );

    _UI.scroll_layout->addWidget( portValue->getWidget() );

    _UIPortValues.push_back( portValue );

};


/**
 * update midi port controls
 */

void ControlPort::updateDropdown() {

    _PortContainers = _App->getServer()
        ->getPatchbay()->getPluginPortContainers();

    vector<Audio::PluginPortContainer*>::iterator it;

    for( it = _PortContainers.begin(); it != _PortContainers.end(); ++ it ) {

        Audio::PluginPortContainer * container = (*it);

        _UI.port_add_dropdown->addItem( container->getName() );

    }

};

} } };

