/**
 * CLI app starter
 */
#pragma once

namespace Orza { namespace CLI {


/**
 * Main class
 */

class App {

    public:

        explicit App( int argc, char **argv );

        ~App();


        /**
         * Display bases
         */

        bool displayHelp();

        bool displayList();


        /**
         * Bool interface
         */

        const bool isHelp();

        const bool isList();

        const bool isMainProgram();


    private:


};

}; };
