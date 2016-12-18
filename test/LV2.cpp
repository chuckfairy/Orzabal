/**
 * LADPSA plugin tests
 *
 */
#include <stdio.h>
#include <iostream>

#include <Audio/Search.h>
#include <LV2/Plugin.h>
#include <LV2/Search.h>

using namespace std;

int main() {

    Audio::Search * searcher = new LV2Search();

    vector<Audio::Plugin*> plugins = searcher->findAll();

    plugins[0]->start();

    //vector<Plugin>::iterator it;

    //for( int i = 0; i < 10; i ++ ) {

    //cout << plugins[i].getName() << "\n";

    //}

    //   for( it = plugins.begin(); it != plugins.end(); ++it ) {
    //
    //       cout << it->getName() << "\n";
    //
    //   }

    return 0;

};
