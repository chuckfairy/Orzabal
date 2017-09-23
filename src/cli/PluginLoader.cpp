/**
 * Plugin loader from cli impl
 */
#include <stdexcept>
#include <iostream>

#include "PluginLoader.h"

#include <Jack/Server.h>
#include <Jack/Midi.h>

#include <LV2/Plugin.h>
#include <LV2/Search.h>

#include <PluginSearch/LoadedPlugins.h>

namespace Orza { namespace CLI {

using PluginSearch::LoadedPlugins;


/**
 * Main func
 */

void PluginLoader( const char * id ) {

    std::cout << "Loading by ID " << id << "\n";

    LoadedPlugins::load();

    LoadedPlugins * search = new LoadedPlugins();

    Audio::Plugin * plugin;

    try {

        plugin = search->getById( id );

    } catch(...) {

        std::cout << "Could not load plugin " << id << "\n";

        return;

    }


    Jack::Server * server = new Jack::Server();

    server->start();
    server->connectDefault();


    //Midi setup

    Jack::Midi * midi = server->getMidi();
    midi->connectDefaults();

    server->getPatchbay()->addPlugin( plugin );

    while( true );

};


/**
 * test run app
 */

void loadTest() {

    LV2::Plugin * newP = (LV2::Plugin*) LoadedPlugins::getAllSearches()[0]->findAll()[78];

    newP->start();
    newP->run();
    newP->updateJackBufferSize( 1024 );
    newP->updateJack( 1024 );

};

}; };
