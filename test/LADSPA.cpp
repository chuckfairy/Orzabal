/**
 * LADPSA plugin tests
 *
 */
#include <stdio.h>
#include <iostream>
#include <LADSPA/LADSPASearch.h>

using namespace std;

int main() {

    LADSPASearch * searcher = new LADSPASearch();

    vector<LADSPAPlugin> plugins = searcher->PluginSearch();

    vector<LADSPAPlugin>::iterator it;

    for( it = plugins.begin(); it != plugins.end(); ++it ) {

        cout << it->getName() << "\n";

    }

    return 0;

};
