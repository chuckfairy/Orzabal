/**
 * CLI app starter
 */
#pragma once

#include <cxxopts/cxxopts.hpp>


namespace Orza { namespace CLI {


/**
 * Main class
 */

class App {

    public:

        explicit App( int argc, char **argv );

        /**
         * Static program specific
         */

        static const char * NAME;

        static const char * NAME_ASCII;

        static const char * DESCRIPTION;

        static const char * VERSION_PADDING;


        /**
         * Display bases
         */

        void displayDefault();

        void displayHeader();

        void displayHelp();

        void displayList();

        void displayPluginTypes();

        void runPlugin();


        /**
         * Bool interface
         */

        const bool isHelp() const;

        const bool isList() const;

        const bool isPluginTypes() const;

        const bool isPluginRun() const;

        const bool isMainProgram() const;


    private:

        /**
         * cxxopts usage
         */

        cxxopts::Options _Options;

};

}; };
