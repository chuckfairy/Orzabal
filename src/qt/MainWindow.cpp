/**
 * Outer window
 *
 */
#include <QHBoxLayout>
#include <QFile>
#include <QTimer>
#include <QIcon>
#include <QDesktopWidget>

#include <Jack/Midi.h>

#include "Layouts/LayoutLoader.h"

#include "Settings/Layout.h"
#include "Pi/Layout.h"
#include "MainWindow.h"
#include "Settings/MidiDeviceDropdown.h"
#include "Resource/Icons.h"
#include "MidiControl/ControlTab.h"


using Orza::App::Layouts::LayoutLoader;
using Orza::App::Resource::Icons;


/**
 * Window construct
 *
 * @Override
 */
MainWindow::MainWindow( QApplication * app, QWidget * parent, Qt::WindowFlags flags ) :
    QMainWindow( parent, 0 ),
    _PluginSearch()
{

    //Main plugins loader

    LoadedPlugins::load();


    //Icons setup

    Icons::setResource( app );


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

    midiDevices = new MidiDeviceDropdown( this );


    //Midi control

    _ControlTab = new ControlTab( this );


    //@TODO Move to layout picker

    _LayoutLoader = new LayoutLoader( this );

    _SettingsLayout = new Layout( this );


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
 * Plugin search
 */

Layout * MainWindow::getSettingsLayout() {

    return _SettingsLayout;

};

/**
 * Layout @TODO use better base
 */

LayoutLoader * MainWindow::getLayoutLoader() {

    return _LayoutLoader;

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
