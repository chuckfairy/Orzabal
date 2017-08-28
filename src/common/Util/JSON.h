/**
 * Json helper
 */
#pragma once

#include <string>

#include <json/json.hpp>

#include "File.h"


using std::string;

using nlohmann::json;


namespace Util { namespace JSON {

/**
 * Main json getter
 */

inline json getFromFile( const char * const fileName ) {

    string file = File::getContents( fileName );

    json output = json::parse( file );

    return output;

};


/**
 * Save data to file
 */

inline void saveToFile( const char * const fileName, json output ) {

    File::setContents( fileName, output.dump() );

};

}; };
