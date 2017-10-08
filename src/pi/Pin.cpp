/**
 * Pin setup impl
 */
#include <stdexcept>
#include <iostream>

#include <wiringPi.h>

#include "Config/Commands.h"
#include "Pin.h"

namespace Orza { namespace Pi {

/**
 * Construct
 */

Pin::Pin( const PinType type, const unsigned int num ) :
    TYPE( type ),
    PIN_NUM( num ),
    IO_TYPE( type == TYPE_LED ? TYPE_OUTPUT : TYPE_INPUT )
{
};


/**
 * Main methods
 */

void Pin::setup() {

    const char * ioType = IO_TYPE == TYPE_OUTPUT
        ? "output"
        : "input";

    const char * pinCommand = Pin::getPinSetupCommand( PIN_NUM, ioType );

    std::cout << "SETUP COMAND : " << pinCommand << "\n";

    system( pinCommand );

    pinMode( PIN_NUM, IO_TYPE == TYPE_OUTPUT ? OUTPUT : INPUT );

    if( TYPE != TYPE_LED ) {

        pullUpDnControl( PIN_NUM, PUD_UP );

    }

};


/**
 * update if button
 *
 */

void Pin::update() {

    if( TYPE == TYPE_LED ) { return; }

    int buttonMode = digitalRead( PIN_NUM );

    if( buttonMode == LOW ) {

        std::cout << "COMMAND STARTING : " << Pin::getPinCommand( TYPE ) << "\n";

        //system( Pin::getPinCommand( TYPE ) );

    }

};


/**
 * Statics
 */

const char * Pin::getPinSetupCommand( const uint8_t pin, const char * type ) {

    char * fullPath = (char*) malloc(
        50
    );

    sprintf( fullPath, "gpio -g mode %i %s", pin, type );

    return fullPath;

};


/**
 * Pin command defaults
 */

const char * Pin::getPinCommand( PinType type ) {

    switch( type ) {

        case TYPE_RESTART:
            return Config::RESTART_COMMAND;

        case TYPE_SHUTDOWN:
            return Config::SHUTDOWN_COMMAND;

        default:
            throw std::runtime_error(
                "Not a valid pin command type"
            );
            break;

    }

};

}; };
