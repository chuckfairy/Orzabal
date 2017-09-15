/**
 * Plugin loader from cli impl
 */
#include <stdexcept>
#include <iostream>

#include "PluginLoader.h"

#include <Jack/Server.h>
#include <Jack/Midi.h>

#include <PluginSearch/LoadedPlugins.h>

namespace Orza { namespace CLI {

using PluginSearch::LoadedPlugins;


/**
 * Main func
 */

void PluginLoader( const char * id ) {

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

}; };

