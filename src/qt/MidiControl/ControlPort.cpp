/**
 * ControlPort widget editor
 */
#include <QMessageBox>

#include <Audio/Port.h>

#include <Jack/Patchbay.h>

#include <MainWindow.h>
#include <Resource/Icons.h>

#include <Widget/Events/RemoveClickEvent.h>

#include "ControlPort.h"


using Orza::App::Resource::Icons;
using Orza::App::Widget::RemoveClickEvent;


namespace Orza { namespace App { namespace MidiControl {


/**
 * Main class
 */

ControlPort::ControlPort( MainWindow * app, Jack::MidiControlPort * p ) :
    _App( app ),
    _ControlPort( p )
{

    _UI.setupUi( this );

    _UI.label->setText( _ControlPort->getName() );


    //Button setup

    setViewButton( _UI.view_btn, _UI.scrollArea );

    setDeleteButton( _UI.delete_btn );


    //Events

    connect( _UI.port_add_btn, SIGNAL( clicked() ), this, SLOT( addControlPortValue() ) );


    updateDropdown();

};


/**
 * deletion
 */

ControlPort::~ControlPort() {

};


/**
 * Remove event char
 */

const char * ControlPort::REMOVE_EVENT = "REMOVE";


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

    _UI.scroll_layout->addWidget( portValue );

    _UIPortValues.push_back( portValue );

    addNode( portValue );

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
