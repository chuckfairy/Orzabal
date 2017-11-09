/**
 * Line edit touch extension
 */
#pragma once

#include <QtCore>
#include <QLineEdit>

#include <Pi/TouchscreenInput.h>


namespace Orza { namespace App { namespace Widget {


class AbstractLineEdit : public QLineEdit {

    Q_OBJECT;

    public:

        AbstractLineEdit() {};


    protected:

        void focusInEvent( QFocusEvent * e ) {

            if( Config::ORZA_BUILD_CONFIG == COnfig::PI ) {

                runKeyboardCommand();

            }

        };

};

}; }; };
