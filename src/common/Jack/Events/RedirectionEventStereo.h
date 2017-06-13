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
class StereoHostInterface;

class RedirectionEventStereo : public Util::Event {

    private:

        StereoHostInterface * _Host;


    public:

        explicit RedirectionEventStereo( StereoHostInterface * );

        void run( void * );

};

};
