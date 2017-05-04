/**
 * Drop down widget
 *
 */
#pragma once

#include "AbstractElement.h"

class AbstractDropdown : public AbstractElement {

    private:

        List<AbstractElement> _list;

    public:

        bool virtual addElement( AbstractElement* e ) = 0;

        bool virtual removeElement() = 0;

}
