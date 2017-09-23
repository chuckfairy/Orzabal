/**
 * Layout base
 */
#pragma once

#include <string>


using std::string;


namespace Orza { namespace App { namespace Layout {

class Layout {

    public:

        /**
         * Getters
         */

        string getName() {

            return _name;

        };


        /**
         * char
         */




    protected:

        Layout();
        ~Layout();

        string _name;

};

}; }; };
