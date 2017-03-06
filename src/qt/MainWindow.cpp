/**
 * Outer window
 *
 */
#include <QHBoxLayout>
#include <QFile>
#include <QIcon>

#include <Jack/Midi.h>

#include "Settings/Layout.h"
#include "MainWindow.h"
#include "widget/EffectsList.h"
#include "Settings/MidiDeviceDropdown.h"

/**
 * Window construct
 *
 * @Override
 */
MainWindow::MainWindow( QWidget * parent, Qt::WindowFlags flags ) :
    QMainWindow( parent, 0 ) {

    UI.setupUi( this );

    //setWindowFlags(Qt::CustomizeWindowHint);
    //setWindowFlags(Qt::FramelessWindowHint);


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


    //@TODO Move to layout picker

    _SettingsLayout = new Layout( this );
    _Layout = new SimpleLayout( this );


    //Icon

    QIcon icon(":icon.png");
    setWindowIcon( icon );

    //UI creation

    QFile styleFile( ":/Styles/MainStyle.qss" );
    styleFile.open( QFile::ReadOnly );

    // Apply the loaded stylesheet
    QString style( styleFile.readAll() );

    UI.centralWidget->setStyleSheet( style );


    UI.horizontalLayout_3->addWidget( effects );
    UI.horizontalLayout_6->addWidget( midiDevices );

    _Server->run();

};

/**
 * Get server
 */

Jack::Server * MainWindow::getServer() {

    return _Server;

};
