/**
 * Main file for raw CLI
 */
#include <cli/App.h>

int main( int argc, char **argv ) {

    Orza::CLI::App * cli = new Orza::CLI::App( argc, argv );

    cli->displayDefault();

    return 0;

};
