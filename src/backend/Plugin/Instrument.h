/**
 * Instrument base
 *
 */
#pragma once

#include <Audio/Plugin.h>


namespace Plugin {


/**
 * Instrument base class
 *
 */

class Instrument : public Plugin {

    private:

        char TYPE = "INSTRUMENT";

    public:

        Instrument() {};
        ~Instrument() {};

};


};
