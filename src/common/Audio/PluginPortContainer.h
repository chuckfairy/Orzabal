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


        /**
         * Get name / label
         */

        char * getName() {

            char * fullName = (char*) malloc(
                sizeof( port->nameString )
                + 255
            );

            sprintf( fullName, "%s:%s", plugin->getName(), port->nameString.c_str() );

            return fullName;

        };

};

};
