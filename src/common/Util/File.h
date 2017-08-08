/**
 * File helpers
 */
#pragma once

#include <string>
#include <fstream>
#include <streambuf>


namespace Util { namespace File {

/**
 * Get a files contents
 */

inline std::string getContents( const char * const fileName ) {

    std::ifstream t( fileName );
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign(
        (std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>()
    );

    return str;

};


/**
 * Main save to file
 */

inline void setContents( const char * const fileName, std::string input ) {

    std::ofstream out( fileName );

    out << input;

    out.close();

};

}; };
