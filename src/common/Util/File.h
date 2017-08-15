/**
 * File helpers
 */
#pragma once

#include <string>
#include <fstream>
#include <streambuf>
#include <stdexcept>

#include <glob.h>
#include <stdio.h>

using std::string;


namespace Util { namespace File {

/**
 * Get a files contents
 */

inline string getContents( const char * const fileName ) {

    std::ifstream t( fileName );
    string str;

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

inline void setContents( const char * const fileName, string input ) {

    std::ofstream out( fileName );

    out << input;

    out.close();

};


//Glob search

inline glob_t getGlob( const char * const searcher ) {

    glob_t buf;

    int err = glob( searcher, GLOB_TILDE, NULL, &buf );

    if( err == 0 && false ) {

        throw std::runtime_error(
            "Glob search failed"
        );

    }

    return buf;

};


/**
 * Basname of
 */

inline string basenameOf( const string& from, const string& to ) {

    string str( to );

    size_t start_pos = str.find( from );

    if( start_pos == string::npos ) {

        return str;

    }

    str.replace( start_pos, from.length(), "" );

    return str;

};

}; };
