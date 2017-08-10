/**
 * Repo manager of plugins
 */
#pragma once

#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include "Plugin.h"
#include <Audio/PluginRepository.h>

using std::vector;


namespace Jack {


/**
 * Search extension
 */

class PluginRepository : public Audio::PluginRepository<Plugin> {

    public:

        /**
         * Virtual class
         */

        explicit PluginRepository() {};
        ~PluginRepository() {};

};

};
