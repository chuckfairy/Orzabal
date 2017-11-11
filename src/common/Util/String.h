/**
 * String helpers
 */
#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>

#include <boost/regex.hpp>

using std::string;
using std::stringstream;
using std::vector;

namespace Util { namespace String {


/**
 * Regex replace proxy
 */

inline string RegexReplace(
    string regexString,
    string replacement,
    string input
) {

    boost::regex regexBoost( regexString );

    return boost::regex_replace( input, regexBoost, replacement );

};


/**
 * String splitter
 */

inline vector<string> split( string inputArg, string delim ) {

    string input( inputArg );
    vector<string> output;
    string token;
    size_t pos = 0;

    while( ( pos = input.find( delim ) ) != string::npos ) {

        token = input.substr( 0, pos );

        output.push_back( token );

        input.erase( 0, pos + delim.length() );

    }

    output.push_back( input );

    return output;

};


/**
 * Float to string
 */

inline string fromFloat( float fl, int percision = 2 ) {

    stringstream stream;

    stream << std::fixed << std::setprecision( percision ) << fl;

    return stream.str();

};

} };
