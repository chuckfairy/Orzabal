/**
 * Plugin port struct
 */
#pragma once

#include "Port.h"
#include "Plugin.h"

namespace Audio  {

struct PluginPortContainer {

    public:

        explicit PluginPortContainer( Plugin * p, Port * pluginPort ) :
            plugin( p ),
            port( pluginPort )
        {}

        Plugin * plugin;

        Port * port;

};

};
