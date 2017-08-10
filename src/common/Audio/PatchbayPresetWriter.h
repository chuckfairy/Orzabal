/**
 * Preset loader base
 */
#pragma once

#include <vector>

#include <json/json.hpp>

#include "Plugin.h"

#include <Util/JSON.h>
#include <Util/File.h>

using std::string;
using std::vector;
using nlohmann::json;


namespace Audio {

class PatchbayPresetWriter {

    public:

         PatchbayPresetWriter();
         ~PatchbayPresetWriter();


        /**
         * Different load methods
         */

        void saveToFile( const char * const fileName, string data ) {

            Util::File::setContents( fileName, data );

        };


        /**
         * Get JSON from audio plugin
         */

        json getJSON( Plugin * p ) {

            json output;

            output["id"] = p->getID();

            output["ports"] = getPortsJSON();

            return output;

        };


        /**
         * Get JSON from vector
         */

        json getJSON( vector<Plugin*> plugins ) {

            json output;

            vector<Plugin*>::const_iterator it;

            for( it = plugins.begin(); it < plugins.end(); ++ it ) {

                output.push_back( getJSON( it ) );

            }

            return output;

        };


        /**
         * Get ports array JSON
         */

        json getPortsJSON( Plugin * p ) {

            json output;

            vector<long> ports = p->getPorts();

            int len = p->getNumPorts();

            for( int i = 0; i < len; ++ i ) {

                json portJSON;

                Port * port = p->getPort( i );

                portJSON["id"] = i;

                output.push_back( portJSON );

            }

            return output;

        };

};

};
