/**
 * Pin setup main
 */
#pragma once

#include <cstdint>

namespace Orza { namespace Pi {

/**
 * Pin types
 */

enum PinType {
    TYPE_LED,
    TYPE_RESTART,
    TYPE_SHUTDOWN
};

enum PinIOType {
    TYPE_INPUT,
    TYPE_OUTPUT
};


/**
 * Main class
 */

class Pin {

    public:

        Pin( const PinType, const unsigned int );


        /**
         * Main methods
         */

        void setup();

        void update();


        /**
         * Statics
         */

        static const char * getPinSetupCommand( const uint8_t, const char * );

        static const char * getPinCommand( PinType );

    private:

        const PinType TYPE;

        const PinIOType IO_TYPE;

        const uint8_t PIN_NUM;

};

}; };
