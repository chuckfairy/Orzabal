/**
 * Input change event handler
 */
#pragma once

#include <Util/Dispatcher.h>

namespace Orza { namespace App {  namespace Settings {

/**
 * Main class
 */


template<typename T>

class InputChangeEvent : Util::Event {

    public:

        InputChangeEvent( T * l ) :
            _Layout( l )
        {};

        void run( void * data ) {

            _Layout->handleInputChange( data );

        };

    private:

        T * _Layout;

};

}; }; };
