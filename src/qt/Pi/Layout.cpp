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

    //Scan

    connect(
        _Tab.scan_btn,
        SIGNAL( clicked() ),
        this,
        SLOT( updateNetworks() )
    );

    //Connect

    connect(
        _Tab.connect_btn,
        SIGNAL( clicked() ),
        this,
        SLOT( connectNetwork() )
    );

};


void Layout::updateNetworks() {

    vector<string> nets = _Manager->getNetworkSSIDs();

    vector<string>::const_iterator it;

    _Tab.ssid_dropdown->clear();

    _Tab.ssid_dropdown->addItem( "-- Select Network --" );

    for( it = nets.begin(); it != nets.end(); ++ it ) {

        _Tab.ssid_dropdown->addItem( (*it).c_str() );

    }

    _Tab.ssid_dropdown->setCurrentIndex( 0 );

};


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
