/**
 * Callback event for jack
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

class JackCallbackEvent : public Util::Event {

    private:

        Host * _Patchbay;


    public:

        /**
         * Construct
         */

        JackCallbackEvent( Host * p ) {

            _Patchbay = p;

        };

        void run( void * o );

};

};
