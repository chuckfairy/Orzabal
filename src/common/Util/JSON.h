/**
 * Json helper
 */
#pragma once

#include <json/json.hpp>

#include "File.h"


using nlohmann::json;


namespace Util { namespace JSON {

/**
 * Main json getter
 */

inline json getFromFile( const char * const fileName ) {

    json output = json::parse( File::getContents( fileName ) );

    return output;

};


/**
 * Save data to file
 */

inline void saveToFile( const char * const fileName, json output ) {

    File::setContents( fileName, output.dump() );

};

}; };
