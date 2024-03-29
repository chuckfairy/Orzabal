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

#include <OrzaPad.h>

//Pi
#ifdef IS_PI
#include "Pi/Layout.h"
#endif

#include "MainWindow.h"
#include <Resource/Icons.h>
#include "Settings/ControlTab.h"

#include <common/Config/Config.h>


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


#ifdef USE_ORZAPAD
	//OrzaPad
	OrzaPad * pad = new OrzaPad(_Server);
	UI.tabWidget->insertTab( 4, pad, "Pad" );
	_Server->getMidi()->addOutput(pad->getOutputPort());
#endif


	//Midi control
	_ControlTab = new ControlTab( this );


	//preset writer and loader setup before settings
	_LayoutLoader = new InstrumentPresetLoader( this, getServer() );
	_LayoutWriter = new InstrumentPresetWriter();// getServer() );

	//Settings
	_SettingsLayout = new Layout( getServer(), _LayoutWriter, _LayoutLoader );

	//Setup current layout settings
	//@TODO load default if no preset passed through
	_LayoutLoader->setup();


	//Icon
	QIcon icon(":icon.png");
	setWindowIcon( icon );

	//UI creation
	QFile styleFile( ":/Styles/DarkStyle.qss" );
	styleFile.open( QFile::ReadOnly );

	// Apply the loaded stylesheet
	QString style( styleFile.readAll() );
	UI.centralWidget->setStyleSheet( style );

	//Settings layout tab
	UI.settings_area->layout()->addWidget(_SettingsLayout);

	//Set version text
	string version = (string)"v" + (string)Orza::Bal::VERSION;
	UI.version_text->setText(version.c_str());


	//Main audio server startup
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
