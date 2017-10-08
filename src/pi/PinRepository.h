/**
 * Pin repo class
 */
#pragma once

#include <Util/Repository.h>

#include "Pin.h"


namespace Orza { namespace Pi {


class PinRepository: public Util::Repository<Pin> {

    public:

        PinRepository();


        /**
         * Pin types
         */

        void setup();

        void update();


        /**
         * Statics
         */

        static PinRepository loadFromDefaultConfig();

};

}; };
