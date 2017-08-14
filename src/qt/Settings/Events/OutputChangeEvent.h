/**
 * Output port change event handler
 */
#pragma once

#include <Util/Dispatcher.h>

#include <Jack/Server.h>

namespace Orza { namespace App {  namespace Settings {

/**
 * Forwarding
 */
class Layout;


/**
 * Main class
 */

class OutputChangeEvent : Util::Event {

    public:

        OutputChangeEvent( Layout * );

        void run( void * );

    private:

        Layout * _Layout;

};

}; }; };
