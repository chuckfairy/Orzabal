/**
 * Repo base
 */
#pragma once

#include <algorithm>
#include <vector>

using std::vector;


namespace Util {

/**
 * Main template
 */

template<typename T>

class Repository {

    protected:

        vector<T*> _items;

    public:

        vector<T*> getAll() {

            return _items;

        };


        /**
         * Optional update manevour
         */

        void update() {};



        void add( T * toAdd ) {

            _items.push( toAdd );

        };

        bool has( T * ) {

            return ( std::find( v.begin(), v.end(), x )  != v.end() );

        };

};

};
