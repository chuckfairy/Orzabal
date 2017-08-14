/**
 * Audio host
 *
 */
#pragma once

#include "Host.h"
#include "Plugin.h"


namespace Audio {


class Patchbay : public Host {

    public:

        vector<Plugin*> getActivePlugins() {

            return _ActivePlugins;

        };


    protected:

        vector<Plugin*> _Plugins;

        vector<Plugin*> _ActivePlugins;

        vector<Plugin*> _ActiveEffects;

};

};
