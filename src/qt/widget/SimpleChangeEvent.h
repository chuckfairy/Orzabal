/**
 * Simple layouts change event
 *
 */
#pragma once

#include <Util/Dispatcher.h>

template <typename T>

class SimpleChangeEvent : public Util::Event {

    private:

        T * _Layout;

    public:

        SimpleChangeEvent( T * t ) :
            _Layout( t )
        {};

        void run( void * data ) {

            _Layout->handleChange( data );

        };

};
