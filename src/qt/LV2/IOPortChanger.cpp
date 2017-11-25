/**
 * IO Port changer ui
 */
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

#include <Widget/InputDropdown.h>
#include <Widget/OutputDropdown.h>

#include <Jack/Host.h>

#include "IOPortChanger.h"

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

    _Dropdown = _port->isInput
        ? (QComboBox*) new InputDropdown( _Server )
        : (QComboBox*) new OutputDropdown( _Server );

    QLabel * label = new QLabel;

    label->setText( _port->nameString.c_str() );

    QVBoxLayout * layout = new QVBoxLayout();

    layout->addWidget( label );

    layout->addWidget( _Dropdown );

    _MainWidget->setLayout( layout );

};


/**
 * Slot for selection change
 */

void IOPortChanger::handleSelectionChanged() {

    connect();

};


/**
 * Main connect
 */

void IOPortChanger::connect() {

    _Server->getAudio()->disconnectJackPort( _port->jack_port );



};

}; }; };
