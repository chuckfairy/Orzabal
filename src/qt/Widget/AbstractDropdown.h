/**
 * Abstact view for default dropdowns
 */
#pragma once

#include <QtCore>
#include <QComboBox>
#include <QListView>

namespace Orza { namespace App { namespace Widget {

class AbstractDropdown : public QComboBox {

    Q_OBJECT;

    protected:

        AbstractDropdown( QWidget * parent );

        AbstractDropdown() {

            setView(new QListView());

        };



};

}; }; };
