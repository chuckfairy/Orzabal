/**
 * Midi control
 */
#pragma once

#include <iostream>

#include <stdlib.h>
#include <inttypes.h>

#include <string>


using std::string;


namespace Orza { namespace Midi {

/**
 * Control enum
 */

enum ControlNumber {
	CONTROL_14 = 14,
	CONTROL_15 = 15,
	CONTROL_16 = 16,
	CONTROL_17 = 17,
	CONTROL_18 = 18,
	CONTROL_19 = 19,
	CONTROL_20 = 20,
	CONTROL_21 = 21,
	CONTROL_22 = 22,
	CONTROL_23 = 23,
	CONTROL_24 = 24,
	CONTROL_25 = 25,
	CONTROL_26 = 26,
	CONTROL_27 = 27,
	CONTROL_28 = 28,
	CONTROL_29 = 29,
	CONTROL_30 = 30,
	CONTROL_31 = 31,

};

const ControlNumber CONTROL_NUMBER_MIN = CONTROL_14;
const ControlNumber CONTROL_NUMBER_MAX = CONTROL_31;


/**
 * Value constants
 */

const uint8_t CONTROL_VALUE_MIN  = 0;
const uint8_t CONTROL_VALUE_MAX = 127;


/**
 * Control range
 */

enum ControlRange {
    RANGE_LINEAR,
    RANGE_LOG
};

/**
 * Midi Control port
 */

template<typename PortType>
struct ControlPort {

    PortType * port;
    const ControlNumber number;
    char * fullName;

    /**
     * Construct
     */

    ControlPort( PortType * p, const ControlNumber n ) :
        port( p ),
        number( n )
    {
    }

    /**
     * Get name / label
     */

    char * getName() {

        fullName = (char*) malloc(
            sizeof( port->nameString )
            + sizeof( number )
            + 50
        );

        sprintf( fullName, "%s:CONTROL_%i", port->nameString.c_str(), number );

        return fullName;

    };

};

}; };
