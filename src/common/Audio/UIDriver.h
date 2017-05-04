/**
 * Audio ui driver, use as add on
 *
 */
#pragma once

namespace Audio {

/**
 * Forwarding
 */
class UI;


/**
 * Main class
 */

class UIDriver {

    public:

        UIDriver() {};
        ~UIDriver() {};


        /**
         * Virtuals
         */

        virtual void start() {};

        virtual void stop() {};

        virtual void update() {};

        void setUI( UI * );

    protected:

        UI * _UI;

};

};
