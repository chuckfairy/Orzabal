/**
 * Line edit touch extension
 */
#pragma once

#include <QtCore>
#include <QLineEdit>

#include <Pi/TouchscreenInput.h>

#include <Config/BuildType.h>

namespace Orza { namespace App { namespace Widget {

template<typename QType>
class BaseEdit : public QType {

    public:

        BaseEdit( QWidget * parent );
        BaseEdit() {};
        ~BaseEdit() {};


    protected:

        void mousePressEvent( QMouseEvent * e ) {

            if( Config::ORZA_BUILD_CONFIG == Config::Pi ) {

                Pi::runKeyboardCommand();

            }

        };

};


/**
 * Types from template
 */

typedef BaseEdit<QLineEdit> BaseLineEdit;


/**
 * Password
 */

class BasePasswordEdit : public BaseEdit<QLineEdit> {

    public:

        BasePasswordEdit() {

            setEchoMode( QLineEdit::Password );

        };

};

}; }; };
