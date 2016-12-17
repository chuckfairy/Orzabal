/**
 * Element base
 *
 */

namespace Plugin {

/**
 *
 *
 */
class Element {

    private:

        const char * TYPE;

        char name[255];

    public:

        /**
         * Get name
         */

        char * getName() {

            return &name;

        };


};

};
