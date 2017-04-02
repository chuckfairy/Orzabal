/**
 * Pi layout
 */
#pragma once


/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace App { namespace Pi {

/**
 * Forwarding
 */


/**
 * Main class
 */

class Layout {


    private:

        /**
         * Fullscreen flag
         */

        bool FULLSCREEN = false;

        MainWindow * _App;


    public:

        Layout( MainWindow * );


        /**
         * Fullscreen Getter
         */

        bool isFullscreen() {

            return FULLSCREEN;

        };


        /**
         * Window actions
         */

        void goFullscreen();

        void goWindowed();


        /**
         * Main toggle method
         */

        void toggleFullscreen();

};

} } };
