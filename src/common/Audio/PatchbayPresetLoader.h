/**
 * Preset loader base
 */
#pragma once

#include <stdexcept>
#include <vector>
#include <iostream>
#include <string>

#include <json/json.hpp>

#include "Config/Config.h"
#include "Plugin.h"

#include <Util/File.h>
#include <Util/JSON.h>
#include <Util/String.h>

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

            json file = Util::JSON::getFromFile( fileName );

            load( file );

        };

        void loadFromName( const char * const name ) {

            char * fullPath = (char*) malloc(
                sizeof( Config::DataDirectory )
                + sizeof( name )
                + 50
            );

            sprintf( fullPath, "%s/%s.json", Audio::Config::DataDirectory, name );

            loadFromJSON( fullPath );

        };


        /**
         * Find all
         */

        glob_t getGlob() {

            char * fullPath = (char*) malloc(
                sizeof( Config::DataDirectory )
                + 50
            );

            sprintf( fullPath, "%s/*.json", Config::DataDirectory );

            return Util::File::getGlob( fullPath );

        };


        /**
         * Get file names as string
         */

        vector<string> getFileNames() {

            glob_t glob_result = getGlob();

            vector<string> ret;

            for( unsigned int i = 0; i < glob_result.gl_pathc; ++i ){

                string filePath( glob_result.gl_pathv[i] );

                //@TODO make better
                filePath = Util::String::RegexReplace( Config::DataDirectory, "", filePath );
                filePath = Util::String::RegexReplace( "^/", "", filePath );
                filePath = Util::String::RegexReplace( ".json$", "", filePath );

                ret.push_back( filePath );

            }

            globfree( &glob_result );

            return ret;

        };


        /**
         * Set ports from value
         */

        void setPortsFromJSON( Plugin * p, json pluginJSON ) {

            json::iterator it;

            for( it = pluginJSON["ports"].begin(); it != pluginJSON["ports"].end(); ++ it ) {

                json portJSON = (*it);

                Port * port = p->getPort( portJSON["id"] );

                p->setPortValue( port, (float) portJSON["value"] );

            }

        };


    protected:

        const char * DIRECTORY = Config::DataDirectory;

};

};
