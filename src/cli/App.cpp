/**
 * CLI base app impl
 */
#include <iostream>
#include <string>
#include <vector>

#include <common/Config/Config.h>
#include <Config/PluginTypes.h>
#include <Util/String.h>

#include "PluginList.h"
#include "PluginLoader.h"

#include "App.h"

using std::string;
using std::vector;

namespace Orza { namespace CLI {


/**
 * Static app chars
 */

const char * App::NAME = "Orzabal";

const char * App::NAME_ASCII = R"(
   ____                _           _
  / __ \              | |         | |
 | |  | |_ __ ______ _| |__   __ _| |
 | |  | | '__|_  / _` | '_ \ / _` | |
 | |__| | |   / / (_| | |_) | (_| | |
  \____/|_|  /___\__,_|_.__/ \__,_|_|
)";

const char * App::DESCRIPTION = "Meta Synth App";

const char * App::VERSION_PADDING = "                               ";


/**
 * Construct
 */

App::App( int argc, char **argv ) :
    _Options( cxxopts::Options( App::NAME, App::DESCRIPTION ) )
{

    _Options.add_options()
        ( "l,list", "List of plugins" )
        ( "p,plugin-types", "Plugin Types Installed" )
        ( "h,help", "Display this message" )
        ( "run", "Run raw midi instrument from CLI", cxxopts::value<std::string>()->default_value(""))
        ( "load", "Load JSON setting", cxxopts::value<std::string>()->default_value("") )
    ;

    _Results = _Options.parse( argc, argv );

};


/**
 * default show
 * show help over list till list help
 */

void App::displayDefault() {

    if( isHelp() ) {

        return displayHelp();

    } else if( isList() ) {

        return displayList();

    } else if( isPluginTypes() ) {

        return displayPluginTypes();

    } else if( isPluginRun() ) {

        return runPlugin();

    }

};


/**
 * Ascii header
 */

void App::displayHeader() {

    std::cout << App::NAME_ASCII << "\n";
    std::cout << App::VERSION_PADDING
        << Orza::Bal::VERSION
        << "\n";

};


/**
 * Display bases
 */

void App::displayHelp() {

    displayHeader();

    std::cout << "\n\n" << _Options.help() << "\n";

};


/**
 * Display plugin types and ids
 */

void App::displayList() {

    PluginList();

};


/**
 * Plugin types list
 */

void App::displayPluginTypes() {

    std::cout << App::NAME << " Version "
        << Orza::Bal::VERSION << "\n"
        << "Plugin Types:\n";

    vector<string> types = Util::String::split(
        Orza::Config::PLUGIN_TYPES,
        ";"
    );

    vector<string>::iterator it;

    for( it = types.begin(); it != types.end(); ++ it ) {

        std::cout << (*it) << "\n";

    }

};


/**
 * Run plugin midi by id
 */

void App::runPlugin() {

    PluginLoader( _Results["run"].as<string>().c_str() );

}


/**
 * Bool interface
 */

const bool App::isHelp() const {

    return _Results["help"].as<bool>();

};

const bool App::isList() const {

    return _Results["list"].as<bool>();

};

const bool App::isPluginTypes() const {

    return _Results["plugin-types"].as<bool>();

};

const bool App::isPluginRun() const {

    return ! _Results["run"].as<string>().empty();

};

const bool App::isMainProgram() const {

    return ! isHelp()
        && ! isList()
        && ! isPluginTypes()
        && ! isPluginRun()
    ;

};

}; };
