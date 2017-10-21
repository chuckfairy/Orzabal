/**
 * Vector helpers
 */
#pragma once

#include <vector>

using std::vector;

namespace Util { namespace Vector {

/**
 * Append vector to vector
 */
template<typename T>
inline void append( vector<T> * source, vector<T> dest ) {

    source->insert( std::end( *source ), std::begin( dest ), std::end( dest ) );

};

}; };
