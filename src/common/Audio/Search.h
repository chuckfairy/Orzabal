/**
 * Search base
 *
 */
#pragma once

#include <vector>

#include "Plugin.h"

using std::vector;


class Search {

    protected:

        const char * _path;


    public:

        Search() {};
        ~Search() {};

        /**
         * Search All
         *
         */
        virtual vector<Plugin> findAll() {

            vector<Plugin> pluginList;

            return pluginList;

        };

};
