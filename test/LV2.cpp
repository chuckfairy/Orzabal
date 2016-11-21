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

   Search * searcher = new LV2Search();

   vector<Plugin> plugins = searcher->findAll();

   vector<Plugin>::iterator it;

   for( it = plugins.begin(); it != plugins.end(); ++it ) {

       cout << it->getName() << "\n";

   }

   return 0;

};
