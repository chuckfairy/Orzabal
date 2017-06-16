/**
 * Buffer event for jack
 *
 */
#pragma once

#include <Util/Dispatcher.h>

namespace Jack {


/**
 * Class forwarding
 *
 */
class Host;


/**
 * Main dispatch, uses plugin
 *
 */

class BufferEvent : public Util::Event {

    private:

        Host * _Patchbay;


    public:

        /**
         * Construct
         */

        BufferEvent( Host * p ) : _Patchbay( p ) {};

        void run( void * o );

};

};
