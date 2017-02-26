/**
 * Outer window
 *
 */
#include <QHBoxLayout>

#include <Jack/Midi.h>

#include "MainWindow.h"
#include "widget/EffectsList.h"
#include "Settings/MidiDeviceDropdown.h"

/**
 * Window construct
 *
 * @Override
 */
MainWindow::MainWindow( QWidget * parent, Qt::WindowFlags flags ) :
    QMainWindow( parent, flags ) {

    UI.setupUi( this );


    //Jack Startup

    _Server = new Jack::Server();

    _Server->start();

    _Server->connectDefault();


    //@TODO Probably move this construction

    LV2::Host * host = _Server->getPatchbay();

    host->setServer( _Server );

    host->setServerCallbacks();


    //Audio setup

    Jack::Host * audio = _Server->getAudio();

    audio->setServerCallbacks();

    Jack::Midi * midi = _Server->getMidi();
    midi->connectDefaults();


    //Widget creation

    dropdown = new InstrumentDropdown( _Server );

    effects = new EffectsList();

    midiDevices = new MidiDeviceDropdown();

    Outputs = new OutputDropdown( _Server );


    //@TODO Move to layout picker

    _Layout = new SimpleLayout( this );


    //UI creation

    UI.horizontalLayout_3->addWidget( effects );
    UI.horizontalLayout_6->addWidget( midiDevices );
    UI.horizontalLayout_5->addWidget( Outputs );

    _Server->run();

};

/**
 * Get server
 */

Jack::Server * MainWindow::getServer() {

    return _Server;

};
