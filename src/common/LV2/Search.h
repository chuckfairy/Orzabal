/**
 * Search for lv2
 *
 */
#pragma once

#include <stdio.h>
#include <string.h>
#include <iostream>

#include <Audio/Plugin.h>

#include <Audio/Search.h>

#include <lilv/lilv.h>

#include "Plugin.h"

class LV2Search : public Search {

    public:

        LV2Search();

        vector<Plugin*> findAll() {

            vector<Plugin*> pluginList;

            LilvWorld* world = lilv_world_new();
            lilv_world_load_all(world);

            const LilvPlugins* plugins = lilv_world_get_all_plugins(world);

            LILV_FOREACH(plugins, i, plugins) {

                const LilvPlugin* p = lilv_plugins_get(plugins, i);

                //Plugin * _p = new LV2Plugin( p );
                Plugin * d = new LV2Plugin( p );

                pluginList.push_back( d );

                //LilvNode* n = lilv_plugin_get_name( p );
                //printf("%s\n", lilv_node_as_string(n));
                //lilv_node_free(n);

            }

            //lilv_world_free(world);

            return pluginList;

        };

};
