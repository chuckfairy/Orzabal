/**
 * Preset loader base
 */
#pragma once

#include <vector>
#include <iostream>
#include <string>

#include <json/json.hpp>

#include "Config/Config.h"

#include <Util/File.h>
#include <Util/JSON.h>

using std::string;
using std::vector;

using nlohmann::json;


namespace Audio {

class PatchbayPresetLoader {

    public:

        PatchbayPresetLoader() {};
        ~PatchbayPresetLoader() {};


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

        void loadFromName( const char * const name );


        /**
         * Find all
         */

        glob_t getGlob() {

            char * fullPath = (char*) malloc(
                sizeof( Config::DataDirectory )
                + 50
            );

            sprintf( fullPath, "%s/*.json", Config::DataDirectory );

            std::cout << fullPath;

            return Util::File::getGlob( fullPath );

        };


        /**
         * Get file names as string
         */

        vector<string> getFileNames() {

            glob_t glob_result = getGlob();

            vector<string> ret;

            for( unsigned int i=0; i < glob_result.gl_pathc; ++i ){

                ret.push_back( string( glob_result.gl_pathv[i] ) );

            }

            globfree( &glob_result );

            return ret;

        };


    protected:

        const char * DIRECTORY = Config::DataDirectory;

};

};
