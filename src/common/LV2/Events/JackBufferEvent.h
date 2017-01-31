/**
 * Buffer event for jack
 *
 */
#pragma once

#include <Util/Dispatcher.h>

namespace LV2 {


/**
 * Class forwarding
 *
 */
class Host;


/**
 * Main dispatch, uses plugin
 *
 */

class JackBufferEvent : public Util::Event {

    private:

        Host * _Patchbay;


    public:

        /**
         * Construct
         */

        JackBufferEvent( Host * p ) {

            _Patchbay = p;

        };

        void run( void * o );

};

};
