/**
 * Jack port register should happen upon starting audio server
 */
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE "Orzabal/CLI/test_cli"

#include <boost/test/unit_test.hpp>

#include <cli/App.h>

#include "include/Argv.h"


/**
 * Main port register
 */

BOOST_AUTO_TEST_CASE( test_cli ) {

    //test help

    Argv helpArgs({ "test", "--help" });

    Orza::CLI::App * app = new Orza::CLI::App( helpArgs.argc(), helpArgs.argv() );

    app->displayHelp();

    BOOST_CHECK( app->isHelp() );


    //test list

    Argv listArgs({ "test", "--list" });

    Orza::CLI::App * listApp = new Orza::CLI::App( listArgs.argc(), listArgs.argv() );

    listApp->displayList();

    BOOST_CHECK( listApp->isList() );


    //test pluginTypes

    Argv pluginTypesArgs({ "test", "--plugin-types" });

    Orza::CLI::App * pluginTypesApp = new Orza::CLI::App(
        pluginTypesArgs.argc(),
        pluginTypesArgs.argv()
    );

    pluginTypesApp->displayPluginTypes();

    BOOST_CHECK( pluginTypesApp->isPluginTypes() );

};
