/**
 * Drop down widget
 *
 */
#pragma once

class AbstractElement {

    private:

        bool SHOWN = false;

    public:

        bool virtual show() = 0;

        bool virtual hide() = 0;

}
