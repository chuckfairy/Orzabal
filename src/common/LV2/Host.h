/**
 * LV2 Host extended from Jack
 *
 */
#pragma once

#include <Jack/Host.h>

#include "Search.h"


namespace LV2 {


/**
 * Construct
 */

class Host : public Jack::Host {

    private:

        LilvWorld * _lilvWorld;

        Search * _Search;

    public:

        Host( jack_client_t * c ) : Jack::Host( c );

};

};
