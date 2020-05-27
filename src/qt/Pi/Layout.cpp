/**
 * Pi layout
 */
#include <stdlib.h>
#include <string>
#include <vector>

#include <pi/Config/Commands.h>

#include <QtCore>

#include <MainWindow.h>

#include "Layout.h"


using std::string;
using std::vector;

namespace Orza { namespace App { namespace Pi {

/**
 * Forwarding
 */


/**
 * Main class
 */

Layout::Layout( MainWindow * app ) :
	_App( app ),
	_WidgetContent( new QWidget() ),
	_WifiPass( new Widget::BasePasswordEdit )
{

	_WidgetContent->setObjectName( "Pi Tab" );

	_Tab.setupUi( _WidgetContent );

	QHBoxLayout * layout = new QHBoxLayout( _WidgetContent );

	int index = app->getUI()->tabWidget->addTab( _WidgetContent, "Pi" );

	_Tab.wifi_pass_layout->addWidget( _WifiPass );


	//Events

	connect( _Tab.windowed, SIGNAL( clicked() ), this, SLOT( toggleFullscreen() ) );

	connect( _Tab.restart_btn, SIGNAL( clicked() ), this, SLOT( handleRestart() ) );

	connect( _Tab.shutdown_btn, SIGNAL( clicked() ), this, SLOT( handleShutdown() ) );


	//Network

	setNetworkManager();

	//VNC and url display updates
	managerDisplayUpdate();


	//Full screen default

	goFullscreen();

};


/**
 * Hardware commands
 */

void Layout::shutdown() {

	system( Orza::Pi::Config::SHUTDOWN_COMMAND );

};

void Layout::restart() {

	system( Orza::Pi::Config::RESTART_COMMAND );

};


/**
 * Fullscreen mode
 */

void Layout::goFullscreen() {

	_App->goFullscreen();

	FULLSCREEN = true;

};


/**
 * windowed
 */

void Layout::goWindowed() {

	_App->goWindowed();

	FULLSCREEN = false;

};


/**
 * Toggle impl
 */

void Layout::toggleFullscreen() {

	if( FULLSCREEN ) {

		goWindowed();

	} else {

		goFullscreen();

	}

};


/**
 * Hardware command slots
 */

void Layout::handleShutdown() {

	shutdown();

};

void Layout::handleRestart() {

	restart();

};


void Layout::setNetworkManager() {

	_Manager = new Network::Manager;

	//Set interfaces
	vector<string> interfaces = _Manager->getInterfaces();

	for(int i = 0; i < interfaces.size(); ++i) {
		if(i == 0) {
			_Manager->setInterface(interfaces[i].c_str());
			managerDisplayUpdate();
		}

		_Tab.interface_dropdown->addItem(interfaces[i].c_str());
	}

	//Scan

	connect(
		_Tab.scan_btn,
		SIGNAL( clicked() ),
		this,
		SLOT( updateNetworks() )
	);

	connect(
		_Tab.interface_dropdown,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(handleInterfaceChange(int))
	);


	//Connect

	connect(
		_Tab.connect_btn,
		SIGNAL( clicked() ),
		this,
		SLOT( connectNetwork() )
	);

};

void Layout::handleInterfaceChange(int index) {

	string s = (string)_Tab.interface_dropdown->itemText(index).toUtf8();
	_Manager->setInterface(s);

	managerDisplayUpdate();

}

void Layout::updateNetworks() {

	vector<string> nets;

	try {
		nets = _Manager->getNetworkSSIDs();
	} catch(std::runtime_error e) {
		std::cout << "NETWORK GRAB ERROR " << e.what() << "\n";
	}

	vector<string>::const_iterator it;

	_Tab.ssid_dropdown->clear();

	_Tab.ssid_dropdown->addItem( "-- Select Network --" );

	for( it = nets.begin(); it != nets.end(); ++ it ) {

		_Tab.ssid_dropdown->addItem( (*it).c_str() );

	}

	_Tab.ssid_dropdown->setCurrentIndex( 0 );

};

void Layout::managerDisplayUpdate() {

	//VNC display
	string vncPortDisplay = _Manager->getIP() + ":" + (string)Orza::Pi::Config::VNC_PORT;
	_Tab.vnc_port_display->setText(vncPortDisplay.c_str());

	//VNC display
	string vncClientDisplay = _Manager->getIP() + ":" + (string)Orza::Pi::Config::VNC_HTML_PORT
		//@TODO maybe redirect
		+ "/vnc.html";
	_Tab.vnc_client_display->setText(vncClientDisplay.c_str());


}


/**
 * Connect ssid
 */

void Layout::connectNetwork() {

	_Manager->connect(
		_Tab.ssid_dropdown->currentText().toStdString(),
		_WifiPass->text().toStdString()
	);

};

}; }; };
