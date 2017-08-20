/**
 * Jack redirector, will take input to output
 * for single interface view
 *
 */
#pragma once

#include <Audio/Plugin.h>
#include <Util/Dispatcher.h>


namespace Orza { namespace App { namespace Widget {

template <class Interface, class Cast> class ActivateClickEvent : public Util::Event {

    public:

        explicit ActivateClickEvent( Interface * i ) : _Host( i ) {

        };


        void run( void * data ) {

            _Host->handleActivateClick( (Cast*) data );

        };


    private:

        Interface * _Host;

};

} } };
