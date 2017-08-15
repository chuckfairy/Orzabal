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

        Plugin * getById( const char * id ) {

            vector<Plugin*>::iterator it;

            vector<T*> items = this->getAll();

            for( it = items.begin(); it != items.end(); ++ it ) {

                Plugin * p = (*it);

                std::cout << "\n" << (*it)->getName();

                return nullptr;

                if( strncmp( p->getID(), id, 500 ) == 0 ) {

                    return p;

                }

            }

            throw std::runtime_error(
                "Id not found"
            );

        };

};

};
