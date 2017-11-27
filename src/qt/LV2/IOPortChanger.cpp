/**
 * IO Port changer ui
 */
#include <vector>

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

#include <Widget/InputDropdown.h>
#include <Widget/OutputDropdown.h>

#include <Jack/Host.h>

#include "IOPortChanger.h"

using std::vector;

using Orza::App::Widget::InputDropdown;
using Orza::App::Widget::OutputDropdown;


namespace Orza { namespace App { namespace LV2UI {


/**
 * Construct
 */

IOPortChanger::IOPortChanger( Jack::Server * s, Jack::Port * port ) :
    _Server( s ),
    _port( port ),
    _MainWidget( new QWidget )
{

    createUI();

};


/**
 * Create UI
 */

void IOPortChanger::createUI() {

    _Dropdown = _port->flow == Audio::FLOW_INPUT
        ? (Widget::AbstractIODropdown*) new InputDropdown( _Server )
        : (Widget::AbstractIODropdown*) new OutputDropdown( _Server );

    QLabel * label = new QLabel;

    label->setText( _port->nameString.c_str() );

    QVBoxLayout * layout = new QVBoxLayout();

    layout->addWidget( label );

    layout->addWidget( _Dropdown );

    _MainWidget->setLayout( layout );

    setDefaultConnected();

    connect(
        _Dropdown,
        SIGNAL( currentIndexChanged( int ) ),
        this,
        SLOT( handleSelectionChanged( int ) )
    );

};


/**
 * Slot for selection change
 */

void IOPortChanger::handleSelectionChanged( int index ) {

    connectPort();

};


/**
 * Main connect
 */

void IOPortChanger::connectPort() {

    _Server->getPatchbay()->disconnectJackPort( _port->jack_port );

    const char * port = _Dropdown->getCurrentJackPort();

    const char * thisPort = jack_port_name( _port->jack_port );

    if( _port->flow == Audio::FLOW_INPUT ) {

        _Server->getPatchbay()->connectJackPort(
            port,
            thisPort
        );

    } else {

        _Server->getPatchbay()->connectJackPort(
            thisPort,
            port
        );

    }

};


/**
 * Default connected checker
 * @TODO check from jack port connection event
 */

void IOPortChanger::setDefaultConnected() {

    vector<const char *> connections = _Server->getPatchbay()->getConnectedPorts( _port );

    if( connections.empty() ) {

        return;

    }


    //Set default from 0
    //@TODO support multi

    std::cout << connections[ 0 ] << " port connected !\n";

};

}; }; };
