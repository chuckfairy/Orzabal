/**
 * Jack redirector, will take input to output
 * for single interface view
 *
 */
#pragma once

#include <inttypes.h>

#include <jack/types.h>

#include <Util/Dispatcher.h>


namespace Jack {

template <class Interface> class RedirectionEventStereo : public Util::Event {

    public:

        explicit RedirectionEventStereo( Interface * i ) : _Host( i ) {

        };


        void run( void * data ) {

            _Host->redirectInput( (jack_nframes_t) (uintptr_t) data );

        };


    private:

        Interface * _Host;

};

};
