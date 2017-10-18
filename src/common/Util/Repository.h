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
         * Param type for vector
         */

        template<typename Param>

            vector<Param*> getAll() {

                typename vector<T*>::iterator it;

                vector<T*> items = this->getAll();

                vector<Param*> output;

                for( it = items.begin(); it != items.end(); ++ it ) {

                    Param * p = (*it);

                    output.push_back( p );

                }

                return output;

            };


        /**
         * Size proxy
         */

        unsigned int size() {

            return _items.size();

        };


        /**
         * Optional update manevour
         */

        void update() {};


        /**
         * Push back add
         */

        void add( T * toAdd ) {

            _items.push_back( toAdd );

        };


        /**
         * Removeal from items
         */

        void remove( T * removal ) {

            _items.erase(
                std::remove( _items.begin(), _items.end(), removal ),
                _items.end()
            );

        };


        /**
         * Has an item
         */

        bool has( T * item ) {

            return (
                std::find( _items.begin(), _items.end(), item )  != _items.end()
            );

        };


        /**
         * Main move
         * Uses std::rotate
         *
         */

        void move( T * item, size_t itemIndex ) {

            int it = getIndex( item );

            std::rotate( it, it + 1, _items.end() );

        };


        /**
         * Empty proxy
         */

        bool empty() {

            return _items.empty();

        };

        void clear() {

            _items.clear();

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

        //vector<T*>::iterator getItemIterator() {

            //return _items.begin();

        //};

        T * getByIndex( int index ) {

            return _items[ index ];

        };


        /**
         * Get index from item
         *
         * @throws std::runtime_error Item not found
         *
         */

        int getIndex( T * item ) {

            typename vector<T*>::iterator itemFind;
            itemFind = std::find(
                _items.begin(),
                _items.end(),
                item
            );

            if( itemFind == _items.end() ) {

                throw std::runtime_error(
                    "Repository::getIndex item not found"
                );

            }

            int index = std::distance( _items.begin(), itemFind );

            return index;

        };

};

};
