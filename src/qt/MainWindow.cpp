/**
 * Outer window
 *
 */
#include <QHBoxLayout>
#include <QFile>
#include <QTimer>
#include <QIcon>

#include <Jack/Midi.h>

#include "Settings/Layout.h"
#include "Pi/Layout.h"
#include "MainWindow.h"
#include "widget/EffectsList.h"
#include "Settings/MidiDeviceDropdown.h"

/**
 * Window construct
 *
 * @Override
 */
MainWindow::MainWindow( QWidget * parent, Qt::WindowFlags flags ) :
    QMainWindow( parent, 0 ),
    _PluginSearch()
{

    //Main plugins loader

    LoadedPlugins::load();


    //QT ui from creator

    UI.setupUi( this );

    setWindowTitle( "Orzabal" );


    //Jack Startup

    _Server = new Jack::Server();

    _Server->start();

    _Server->connectDefault();


    //Midi setup

    Jack::Midi * midi = _Server->getMidi();
    midi->connectDefaults();


    //Widget creation

    dropdown = new InstrumentDropdown( getPluginSearch() );

    effects = new EffectsList();

    midiDevices = new MidiDeviceDropdown( this );


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

    //UI.horizontalLayout_3->addWidget( effects );
    UI.horizontalLayout_6->addWidget( midiDevices );


    //First tab default

    getUI()->tabWidget->setCurrentIndex( 0 );


    //Main startup

    _Server->run();


    //Pi full screen startup

    if( BUILD_TYPE == Config::Pi ) {

         _Pi = new Orza::App::Pi::Layout( this );

        //QTimer::singleShot( 1000, this, SLOT( goFullscreen() ) );

    }

};

/**
 * Get server
 */

Jack::Server * MainWindow::getServer() {

    return _Server;

};


/**
 * Plugin search
 */

LoadedPlugins * MainWindow::getPluginSearch() {

    return &_PluginSearch;

};


/**
 * Layout @TODO use better base
 */

SimpleLayout * MainWindow::getLayout() {

    return _Layout;

};


/**
 * Window actions
 */

void MainWindow::goFullscreen() {

    setWindowFlags( Qt::CustomizeWindowHint );
    setWindowFlags( Qt::FramelessWindowHint );

    showFullScreen();

};

void MainWindow::goWindowed() {

    Qt::WindowFlags flag = windowFlags();
    flag = flag & (~Qt::CustomizeWindowHint) & (~Qt::FramelessWindowHint);

    setWindowFlags( flag );

    show();

    showNormal();

};
