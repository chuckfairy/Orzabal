/**
 * Basic control interface
 */
#pragma once

namespace Audio {

class ControlInterface {

    public:

        /**
         * Virtual override methods
         */

        virtual void start() {};
        virtual void stop() {};
        virtual void run() {};
        virtual void pause() {};


        /**
         * Main active use methods
         */

        bool isActive() {

            return ACTIVE;

        };

        void setActive( bool now ) {

            ACTIVE = now;

        };


    protected:

        ControlInterface() {};
        ~ControlInterface() {};


    private:

        bool ACTIVE = false;

};

};
