/**
 * IO Port changer ui
 */
#pragma once

#include <jack/jack.h>

#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QComboBox>

#include <Jack/Server.h>
#include <Jack/Port.h>

#include <Widget/AbstractIODropdown.h>


namespace Orza { namespace App { namespace LV2UI {

class IOPortChanger : public QWidget {

    Q_OBJECT;

    public:

        IOPortChanger( QWidget * );

        explicit IOPortChanger( Jack::Server *, Jack::Port * );


        /**
         * Main widget getter
         */

        QWidget * getWidget() {

            return _MainWidget;

        };


    public slots:

        void handleSelectionChanged( int );


    private:

        Jack::Server * _Server;

        Jack::Port * _port;

        Widget::AbstractIODropdown * _Dropdown;

        QWidget * _MainWidget;


        /**
         * Create UI
         */

        void createUI();


        /**
         * Main connect
         */

        void connectPort();


        /**
         * Check port connection
         */

        void setDefaultConnected();

};


}; }; };
