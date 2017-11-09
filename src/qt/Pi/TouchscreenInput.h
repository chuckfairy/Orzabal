/**
 * Touchscreen input setters
 */
#pragma once

#include <stdlib.h>

#include <pi/Config/Commands.h>

#include <QtCore>


namespace Orza { namespace App { namespace Pi {

void setHandlers( QWidget * widget ) {

    //widget->connect(

};

void runKeyboardCommand() {

    std::cout << "TEST\n" ;

    system( Orza::Pi::Config::KEYBOARD_COMMAND );

};

}; }; };
