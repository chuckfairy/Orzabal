/**
 * Event message
 */
#pragma once

#include <Util/Dispatcher.h>

#include <Midi/Events.h>


namespace Orza { namespace Midi {

template <typename T>
class EventMessage : public Util::Event {

    public:

        EventMessage( T * t ) :
            _Handler( t )
        {};

        void run( void * data ) {

            _Handler->onMidiMessage( (Midi::Event*) data );

        };


    private:

        T * _Handler;

};

}; };
