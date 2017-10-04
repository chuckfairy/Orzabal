/**
 * Layout base
 */
#pragma once

#include <string>

#include <Audio/PatchbayPresetLoader.h>

using std::string;


namespace Orza { namespace App { namespace Layouts {


/**
 * Main interface
 */

class Layout : public Audio::PatchbayPresetLoader {

    public:

        /**
         * Getters
         */

        string getName() {

            return _name;

        };


        /**
         * Virtuals
         */

        virtual void setup() {};

        virtual void takedown() {};

        virtual void load( json j ) = 0;


    protected:

        Layout() {};
        ~Layout() {};

        string _name;

};

}; }; };
