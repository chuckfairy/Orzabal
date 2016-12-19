/**
 * Audio host p
 *
 *
 */
#pragma once

namespace Audio {

class Host {

    public:

        Host() {};
        ~Host() {};

        virtual unsigned int getSampleRate() {

            return 44100;

        };

};

};
