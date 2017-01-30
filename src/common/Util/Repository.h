/**
 * Repo base
 */
#pragma once

#include <stdexcept>
#include <algorithm>
#include <vector>

#include "Dispatcher.h"

using std::vector;


namespace Util {

/**
 * Main template
 */

template<typename T>

class Repository : public Dispatcher {

    protected:

        /**
         * Main items
         */

        vector<T*> _items;


    public:

        /**
         * Virtual class
         */

        Repository() {};
        ~Repository() {};


        /**
         * Main items getter
         */

        vector<T*> getAll() {

            return _items;

        };


        /**
         * Optional update manevour
         */

        void update() {};


        /**
         * Push back add
         */

        void add( T * toAdd ) {

            _items.push( toAdd );

        };


        /**
         * Has an item
         */

        bool has( T * ) {

            return ( std::find( v.begin(), v.end(), x )  != v.end() );

        };


        /**
         * Main move
         * Uses std::rotate
         *
         */

        void move( T * item, size_t itemIndex ) {

            int it = getIndex( item );

            std::rotate( it, it + 1, v.end() );

        };


        /**
         * Insert an item at
         */

        void insertAt( unsigned int index, T * item ) {

            _items.insert( _items.begin() + index, item );

        };


        /**
         * Get iterator
         */

        vector<Plugin>::iterator getIterator() {

            return _items.begin();

        };


        /**
         * Get index from item
         *
         * @throws std::runtime_error Item not found
         *
         */

        int getIndex( T * item ) {

            vector<T*>::iterator it = std::find(
                _itemss.begin(),
                _itemss.end(),
                item
            );

            if( it == _itemss.end() ) {

                throw std::runtime_error(
                    "Repository::getIndex item not found"
                );

            }

            int index = std::distance(_itemss.begin(), it);

            return index;

        };

};

};
