/**
 * Plugin repo
 */
#pragma once

#include <vector>
#include <string.h>
#include <iostream>
#include <stdexcept>

#include "Plugin.h"
#include <Util/Repository.h>

using std::vector;


namespace Audio {


/**
 * Search extension
 */

template<typename T>
class PluginRepository : public Util::Repository<T> {

    public:

        /**
         * Virtual class
         */

        explicit PluginRepository() {};
        ~PluginRepository() {};


        /**
         * Main id getter
         */

        Plugin * getById( const char * const id ) {

            vector<Plugin*>::iterator it;

            vector<T*> _items = this.getAll();

            for( it = _items.begin(); it != _items.end(); ++ it ) {

                Plugin * p = (Plugin*)(*it);

                if( strncmp( p->getID(), id, sizeof( id ) == 0 ) ) {

                    return p;

                }

            }

            throw std::runtime_error(
                "Id not found"
            );

        };

};

};
