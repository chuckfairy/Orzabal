/**
 * Patchbay effects list and jack port connection
 *
 */
#pragma once

#include <jack/jack.h>

#include "StereoHostInterface.h"


namespace Jack {

/**
 * Output stereo class
 */

class PatchbayEffectsOutput : public StereoHostInterface {

    public:

        explicit PatchbayEffectsOutput( jack_client_t * c ) :
            StereoHostInterface( c )
        {

            createPorts();

        };


        /**
         * Prefix virtual
         */

        const char * getPrefix() {

            return "effects-output";

        };

};

};
