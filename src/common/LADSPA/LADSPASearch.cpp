/**
 * Plugin search class
 *
 */
#include <dirent.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <sstream>

#include "ladspa.h"
//#include "utils.h"

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

    if (!pcLADSPAPath) {

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
        ?  iNeedSlash = false
        : iNeedSlash = true;

    psDirectory = opendir(pcDirectory);

    if( !psDirectory ) {

        return pluginList;

    }


    //Loop thru dir

    while( ( psDirectoryEntry = readdir( psDirectory ) ) ) {

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

        fDescriptorFunction =
            (LADSPA_Descriptor_Function)dlsym(pvPluginHandle, "ladspa_descriptor");


        // We've successfully found a ladspa_descriptor function.

        if( dlerror() == NULL && fDescriptorFunction ) {

            //fCallbackFunction(pcFilename,
                    //pvPluginHandle,
                    //fDescriptorFunction);

            const LADSPA_Descriptor * desc;
            long i, j;

            //printf("%s:\n", fn);
            for (i = 0; (desc = fDescriptorFunction(i)) != NULL; i++) {

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
    //const char * pcLADSPAPath;
    const char * pcStart;

    vector<LADSPAPlugin> dirVecs;

    std::stringstream ss;
    ss.str( pcLADSPAPath );

    string item;

    while( std::getline(ss, item, ':') ) {

        vector<LADSPAPlugin> dirVec = DirectoryPluginSearch( item.c_str() );

        for( vector<LADSPAPlugin>::iterator itVec = dirVec.begin(); itVec != dirVec.end(); ++itVec ) {

            dirVecs.push_back( *itVec );

        }

    }

    //vector<string> directoryLines;

    //bost::split( directoryLines, pcLADSPAPath, boost::is_any_of(":") );

    //for(
    //vector<string>::iterator it = directoryLines.begin();
    //it != directoryLines.end();
    //++it
    //) {

    //vector<LADSPAPlugin> dirVec = DirectoryPluginSearch( *it );

    //for( vector<string>::iterator itVec = dirVec.begin(); itVec != dirVec.end(); ++itVec ) {

    ////dirVecs;

    //}

    //}

    return dirVecs;

};


//static void describePluginLibrary(const char * fn, void * handle, LADSPA_Descriptor_Function descFunc) {

//const LADSPA_Descriptor * desc;

//long i, j;

////printf("%s:\n", fn);
//for (i = 0; (desc = descFunc(i)) != NULL; i++) {
//printf("# %lu %s\n", desc->UniqueID, desc->Name);
////        printf("# %lu %s -- %s\n", desc->UniqueID, desc->Name, desc->Maker);
////        printf("# %lu %s  <%s>\n", desc->UniqueID, desc->Name, desc->Label);

//for(j = 0; j < desc->PortCount; j++) {
//LADSPA_PortRangeHintDescriptor hint = desc->PortRangeHints[j].HintDescriptor;

//if(LADSPA_IS_PORT_INPUT(desc->PortDescriptors[j])) {
//printf(">");
//} else if(LADSPA_IS_PORT_OUTPUT(desc->PortDescriptors[j])) {
//printf("<");
//}

//if(LADSPA_IS_PORT_CONTROL(desc->PortDescriptors[j]))
//printf(" k:");
//else if(LADSPA_IS_PORT_AUDIO(desc->PortDescriptors[j]))
//printf(" a:");

//printf(" %s",desc->PortNames[j]);

//if(LADSPA_IS_HINT_BOUNDED_BELOW(hint) || LADSPA_IS_HINT_BOUNDED_ABOVE(hint)) {
//if(LADSPA_IS_HINT_BOUNDED_BELOW(hint))
//printf(" (%g", desc->PortRangeHints[j].LowerBound);
//else
//printf(" (...");
//printf(" to ");
//if(LADSPA_IS_HINT_BOUNDED_ABOVE(hint))
//printf("%g)", desc->PortRangeHints[j].UpperBound);
//else
//printf("...)");
//}
//printf("\n");
//}
//printf("\n");
//}
//dlclose(handle);
//};
