/**
 * Qt awesome icon resource
 */
#pragma once

#include <QtAwesome/QtAwesome.h>
#include <QApplication>
#include <QIcon>

namespace Orza { namespace App { namespace Resource {

class Icons {

    public:

        /**
         * Getters
         */

        static QtAwesome * getResource();

        static void setResource( QApplication * );

        static QIcon getIcon( int );
        static QFont getFont( int size );

    private:

        static QtAwesome * AWESOME;

};

}; }; };
