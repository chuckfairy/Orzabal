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
class Plugin;


/**
 * Main dispatch, uses plugin
 *
 */

class CallbackEvent : public Util::Event {

    private:

        Plugin * _Plugin;

    public:

        /**
         * Construct
         */

        CallbackEvent( Plugin * p ) {

            _Plugin = p;

        };

        void run( void * o );

};

};
