/**
 * Plugin search class
 *
 */
#pragma once

#include <dirent.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "LADSPAPlugin.h"

using std::vector;


/**
 * LADSPA searcher
 *
 */

class LADSPASearch {

    private:

        const char * pcLADSPAPath;

    public:

        LADSPASearch();


        /**
         * Search just the one directory.
         *
         */

        vector<LADSPAPlugin> DirectoryPluginSearch (
                const char * pcDirectory
            );


        /**
         * Full plugin search
         *
         */

        vector<LADSPAPlugin> PluginSearch();

};
