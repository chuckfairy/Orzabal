/**
 * Lilv world resource
 *
 */
#pragma once

#include <lilv/lilv.h>


namespace LV2 { namespace Resource {

class World {

    public:

        static LilvWorld * getResource();


    private:

        World() {};
        ~World() {};

        /**
         * singleton property
         */

        static LilvWorld * RESOURCE;

};

}; };
