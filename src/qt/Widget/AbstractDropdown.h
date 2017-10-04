/**
 * Abstact view for default dropdowns
 */
#pragma once

#include <QtCore>

namespace Orza { namespace App { namespace Widget {

class AbstractDropdown : public QComboBox {

    Q_OBJECT;

    protected:

        AbstractDropdown() {

            setView(new QListView());

        };



};

}; }; };
