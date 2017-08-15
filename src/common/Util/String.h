/**
 * String helpers
 */
#pragma once

#include <string>

#include <boost/regex.hpp>

using std::string;

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

} };
