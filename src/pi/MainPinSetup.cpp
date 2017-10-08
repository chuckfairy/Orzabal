/**
 * Pin setup main
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <wiringPi.h>

#include <iostream>

#include "Pin.h"
#include "PinRepository.h"

using namespace Orza::Pi;


const unsigned int WAIT_TIME = 100;


/**
 * Main program
 */

int main( void ) {

    std::cout << "Raspberry Pi button\n";

    if( wiringPiSetupGpio() == -1 ) {
        printf( "Failed to setup\n" );
        return 1;
    }

    PinRepository repo = PinRepository::loadFromDefaultConfig();

    repo.setup();

    while( true ) {

        repo.update();

        usleep( WAIT_TIME );

    }

    return 0 ;
}
