/**
 * Registration data passing through event
 */
#pragma once

#include <jack/types.h>

namespace Jack { namespace Events {

struct PortRegistrationData {

    jack_port_id_t id;


    /**
     * Register non 0 for if registered
     */

    int registry = 0;

    bool isRegistered() {

        return registry != 0;

    };


    /**
     * Construct
     */

    explicit PortRegistrationData( jack_port_id_t i, int r ) :
        id( i ),
        registry( r )
    {
    };

};


}; };
