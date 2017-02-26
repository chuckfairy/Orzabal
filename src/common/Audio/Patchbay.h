/**
 * Audio host
 *
 */
#pragma once

#include "Host.h"
#include "Plugin.h"


namespace Audio {


class Patchbay : public Host {

    protected:

        vector<Plugin*> _Plugins;

        vector<Plugin*> _ActivePlugins;

};

};
