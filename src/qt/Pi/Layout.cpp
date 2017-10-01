/**
 * Pi layout
 */
#include <stdlib.h>

#include <pi/Config/Commands.h>

#include <QtCore>

#include <MainWindow.h>

#include "Layout.h"


namespace Orza { namespace App { namespace Pi {

/**
 * Forwarding
 */


/**
 * Main class
 */

Layout::Layout( MainWindow * app ) :
    _App( app ),
    _WidgetContent( new QWidget() )
{

    _WidgetContent->setObjectName( "Pi Tab" );

    _Tab.setupUi( _WidgetContent );

    QHBoxLayout * layout = new QHBoxLayout( _WidgetContent );

    int index = app->getUI()->tabWidget->addTab( _WidgetContent, "Pi" );


    //Events

    connect( _Tab.windowed, SIGNAL( clicked() ), this, SLOT( toggleFullscreen() ) );

    connect( _Tab.restart_btn, SIGNAL( clicked() ), this, SLOT( handleRestart() ) );

    connect( _Tab.shutdown_btn, SIGNAL( clicked() ), this, SLOT( handleShutdown() ) );

    goFullscreen();

};


/**
 * Hardware commands
 */

void Layout::shutdown() {

    system( Orza::Pi::Config::SHUTDOWN_COMMAND );

};

void Layout::restart() {

    system( Orza::Pi::Config::SHUTDOWN_COMMAND );

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

} } };
