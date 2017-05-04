/**
 * Window object
 *
 */
#pragma once

class AbstractWindow {

    private:

        bool SHOWN = false;

    public:

        void virtual show() = 0;
        void virtual hide() = 0;

}
