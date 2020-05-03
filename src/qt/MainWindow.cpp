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


//Pi
#ifdef IS_PI
#include "Pi/Layout.h"
#endif

#include "MainWindow.h"
#include <Resource/Icons.h>
#include "Settings/ControlTab.h"


using Orza::Layouts::LayoutLoader;
using Orza::Resource::Icons;

using Orza::MidiControl::ControlTab;
using Orza::Settings::InstrumentPresetLoader;
using Orza::Settings::InstrumentPresetWriter;


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


	//Midi control

	_ControlTab = new ControlTab( this );


	//preset writer and loader setup before settings
	_LayoutLoader = new InstrumentPresetLoader( this, getServer() );
	_LayoutWriter = new InstrumentPresetWriter();// getServer() );

	//Settings
	_SettingsLayout = new Layout( getServer() );


	//Icon

	QIcon icon(":icon.png");
	setWindowIcon( icon );

	//UI creation

	QFile styleFile( ":/Styles/DarkStyle.qss" );
	styleFile.open( QFile::ReadOnly );

	// Apply the loaded stylesheet
	QString style( styleFile.readAll() );

	UI.centralWidget->setStyleSheet( style );

	UI.settings_area->setWidget(_SettingsLayout);

	//UI.horizontalLayout_3->addWidget( effects );


	//Main startup

	_Server->run();


	//Pi full screen startup

#ifdef IS_PI

	new Orza::App::Pi::Layout( this );

	//QTimer::singleShot( 1000, this, SLOT( goFullscreen() ) );

#endif

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

InstrumentPresetLoader * MainWindow::getLayoutLoader() {

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
