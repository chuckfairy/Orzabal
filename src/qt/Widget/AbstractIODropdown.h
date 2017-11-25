/**
 * Abstact view for default dropdowns
 */
#pragma once

#include <QtCore>

#include "AbstractDropdown.h"


namespace Orza { namespace App { namespace Widget {


class AbstractIODropdown : public AbstractDropdown {

    Q_OBJECT;

    public:

        virtual const char * getCurrentJackPort() { return nullptr; };


    protected:

        AbstractIODropdown() : AbstractDropdown() {};


};

}; }; };
