/**
 * Touchscreen input setters
 */
#pragma once

#include <stdlib.h>

#include <pi/Config/Commands.h>

#include <QtCore>


namespace Orza { namespace App { namespace Pi {

inline void setHandlers( QWidget * widget ) {

    //widget->connect(

};

inline void runKeyboardCommand() {

    system( Orza::Pi::Config::KEYBOARD_COMMAND );

};

}; }; };
