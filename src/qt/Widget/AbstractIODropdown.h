/**
 * Abstact view for default dropdowns
 */
#pragma once

#include <QtCore>
#include <QComboBox>

#include "AbstractDropdown.h"


namespace Orza { namespace App { namespace Widget {


class AbstractIODropdown : public AbstractDropdown {

    Q_OBJECT;

    public:

        virtual const char * getCurrentJackPort() { return nullptr; };


    public:

        AbstractIODropdown( QWidget * parent );

        AbstractIODropdown() : AbstractDropdown() {};


};

}; }; };
