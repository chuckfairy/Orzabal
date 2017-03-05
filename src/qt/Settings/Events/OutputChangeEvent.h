/**
 * Output port change event handler
 */
#pragma once

#include <Util/Dispatcher.h>

#include <Jack/Server.h>

namespace Orza { namespace Qt {  namespace Settings {

/**
 * Forwarding
 */
class Layout;


/**
 * Main class
 */

class OutputChangeEvent : Util::Event {

    private:

        Layout * _Layout;

    public:

        OutputChangeEvent( Layout * );

        void run( void * );

};

}; }; };
