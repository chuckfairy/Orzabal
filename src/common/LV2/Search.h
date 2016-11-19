/**
 * Search for lv2
 *
 */
#pragma once

#include <stdio.h>
#include <string.h>

#include <Audio/Plugin.h>

#include <Audio/Search.h>

#include <lilv/lilv.h>

#include "lilv_config.h"

class LV2Search : public Search {

    public:

        LV2Search();

        vector<Plugin> findAll() {

            vector<Plugin> pluginList;

            LilvWorld* world = lilv_world_new();
            lilv_world_load_all(world);

            const LilvPlugins* plugins = lilv_world_get_all_plugins(world);

            //list_plugins(plugins, show_names);

            lilv_world_free(world);

            return pluginList;

        };

};
