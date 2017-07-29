/**
 * Random utils
 */
#pragma once

#include <cstdlib>

namespace Util {

/**
 * Random string creator
 */

char * random_string( char * output, const unsigned int len ) {

    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for( int i = 0; i < len; ++i ) {

        output[i] = alphanum[ rand() % ( sizeof( alphanum ) - 1 ) ];

    }

    output[len] = 0;

    return output;

};

};
