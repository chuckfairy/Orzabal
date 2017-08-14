/**
 * Preset loader base
 */
#pragma once

#include <vector>

#include <json/json.hpp>

#include <Util/JSON.h>
#include <Util/File.h>

#include "Config/Config.h"
#include "Plugin.h"


using std::string;
using std::vector;
using nlohmann::json;


namespace Audio {

class PatchbayPresetWriter {

    public:

         PatchbayPresetWriter() {};
         ~PatchbayPresetWriter() {};


        /**
         * Different load methods
         */

        void saveToFile( const char * const fileName, string data ) {

            char * fullPath = (char*) malloc(
                sizeof( fileName )
                + sizeof( Config::DataDirectory )
                + 50
            );

            sprintf( fullPath, "%s/%s.json", Config::DataDirectory, fileName );

            std::cout << fullPath << "\n";

            Util::File::setContents( fullPath, data );

        };


        void saveToFile( const char * const fileName, json data ) {

            saveToFile( fileName, data.dump( 4 ) );

        };


        /**
         * Get JSON from audio plugin
         */

        json getJSON( Plugin * p ) {

            json output;

            output["id"] = p->getID();

            output["ports"] = getPortsJSON( p );

            return output;

        };


        /**
         * Get JSON from vector
         */

        json getJSON( vector<Plugin*> plugins ) {

            json output;

            vector<Plugin*>::const_iterator it;

            for( it = plugins.begin(); it < plugins.end(); ++ it ) {

                output.push_back( getJSON( (*it) ) );

            }

            return output;

        };


        /**
         * Get ports array JSON
         */

        json getPortsJSON( Plugin * p ) {

            json output;

            int len = p->getNumPorts();

            for( int i = 0; i < len; ++ i ) {

                json portJSON;

                Port * port = p->getPort( i );

                portJSON["id"] = i;

                portJSON["value"] = port->control;

                output.push_back( portJSON );

            }

            return output;

        };

};

};
