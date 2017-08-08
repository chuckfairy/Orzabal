/**
 * Preset loader base
 */
#pragma once

#include <json/json.hpp>

#include <Util/JSON.h>

using nlohmann::json;


namespace Audio {

class PatchbayPresetLoader {

    public:

        /**
         * Virtuals
         */

        virtual void load( json setting ) {};


        /**
         * Different load methods
         */

        void loadFromJSON( const char * const fileName ) {

            load( Util::JSON::getFromFile( fileName ) );

        };


        PatchbayPresetLoader() {};
        ~PatchbayPresetLoader() {};

};

};
