/**
 * Plugin search class
 *
 */
#include <dirent.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <sstream>

#include "ladspa.h"

#include "LADSPASearch.h"
#include "LADSPAPlugin.h"

#include <boost/algorithm/string.hpp>


using std::vector;
using std::string;


/**
 * Construct
 *
 */

LADSPASearch::LADSPASearch() {

    pcLADSPAPath = getenv("LADSPA_PATH");

    if( ! pcLADSPAPath ) {

#ifdef __APPLE__
        pcLADSPAPath = "/Library/Audio/Plug-Ins/LADSPA";
#else
        pcLADSPAPath = "/usr/lib/ladspa:/usr/local/lib/ladspa";
#endif

    }

};


/**
 * Single directory search
 *
 */

vector<LADSPAPlugin> LADSPASearch::DirectoryPluginSearch( const char * pcDirectory ) {

    char * pcFilename;
    DIR * psDirectory;
    LADSPA_Descriptor_Function fDescriptorFunction;
    long lDirLength;
    bool iNeedSlash;
    struct dirent * psDirectoryEntry;
    void * pvPluginHandle;

    vector<LADSPAPlugin> pluginList;

    lDirLength = strlen(pcDirectory);

    if (!lDirLength) {
        return pluginList;
    }

    iNeedSlash = (pcDirectory[lDirLength - 1] == '/')
        ?  false
        : true;

    psDirectory = opendir(pcDirectory);

    if( !psDirectory ) {

        return pluginList;

    }


    //Loop thru dir

    while( 1 ) {

        psDirectoryEntry = readdir( psDirectory );

        if( ! psDirectoryEntry ) {
            closedir(psDirectory);
            return pluginList;
        }

        pcFilename = (char*) malloc(lDirLength
                + strlen(psDirectoryEntry->d_name)
                + 1 + iNeedSlash);

        strcpy(pcFilename, pcDirectory);

        if( iNeedSlash ) {

            strcat(pcFilename, "/");

        }

        strcat(pcFilename, psDirectoryEntry->d_name);

        pvPluginHandle = dlopen(pcFilename, RTLD_LAZY);


        // This is a file and the file is a shared library!

        if( ! pvPluginHandle ) { continue; }

        dlerror();

        fDescriptorFunction = (LADSPA_Descriptor_Function)dlsym(pvPluginHandle, "ladspa_descriptor");


        // We've successfully found a ladspa_descriptor function.

        if( dlerror() == NULL && fDescriptorFunction ) {

            const LADSPA_Descriptor * desc;
            long i;

            for (i = 0; (desc = fDescriptorFunction(i)) != NULL; i++) {

                //LADSPAPlugin * pluginToAdd = new LADSPAPlugin( desc );
                LADSPAPlugin pluginToAdd( desc );
                pluginList.push_back( pluginToAdd );

            }

            dlclose( pvPluginHandle );
            free(pcFilename);

        } else {

            // not a LADSPA lib. Unload it.

            dlclose(pcFilename);
            free(pcFilename);

        }

    }

    closedir(psDirectory);

    return pluginList;

};


/**
 * Full directories plugin search
 *
 */
vector<LADSPAPlugin> LADSPASearch::PluginSearch() {

    char * pcBuffer;
    const char * pcEnd;
    const char * pcStart;

    vector<LADSPAPlugin> dirVecs;

    std::stringstream ss;
    ss.str( pcLADSPAPath );

    string item;

    while( std::getline( ss, item, ':' ) ) {

        const char * itemC = item.c_str();

        vector<LADSPAPlugin> dirVec = DirectoryPluginSearch( itemC );

        for( vector<LADSPAPlugin>::iterator itVec = dirVec.begin(); itVec != dirVec.end(); ++itVec ) {

            dirVecs.push_back( *itVec );

        }

    }

    return dirVecs;

};
