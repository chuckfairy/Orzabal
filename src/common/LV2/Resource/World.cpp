/**
 * Resource impl
 */

#include "World.h"


namespace LV2 { namespace Resource {


LilvWorld * World::RESOURCE = nullptr;


/**
 * Singleton method
 */

LilvWorld * World::getResource() {

    if( World::RESOURCE == nullptr ) {

        World::RESOURCE = lilv_world_new();
        lilv_world_load_all( World::RESOURCE );

    }

    return World::RESOURCE;

};

}; };
