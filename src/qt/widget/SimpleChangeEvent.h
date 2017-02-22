/**
 * Simple layouts change event
 *
 */
#pragma once

#include <Util/Dispatcher.h>

/**
 * Forwarding
 */
class SimpleLayout;

class SimpleChangeEvent : public Util::Event {

    private:

        SimpleLayout * _Layout;

    public:

        SimpleChangeEvent( SimpleLayout * );

        void run( void * );

};
