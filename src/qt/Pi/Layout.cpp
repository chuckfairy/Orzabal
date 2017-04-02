/**
 * Pi layout
 */
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

Layout::Layout( MainWindow * app ) : _App(app) {

    goFullscreen();

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

} } };
