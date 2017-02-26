/**
 * Jack redirector, will take input to output
 * for single interface view
 *
 */
#pragma once

#include <Util/Dispatcher.h>


namespace Jack {

/**
 * Forwarding
 */
class Host;

class RedirectionEvent : public Util::Event {

    private:

        Host * _Host;


    public:

        explicit RedirectionEvent( Host * );

        void run( void * );

};

};
