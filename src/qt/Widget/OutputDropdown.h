/**
 * Output jack device dropdown
 *
 */
#pragma once


#include <vector>

#include <QtCore>
#include <QtGui>
#include <QComboBox>

#include <Util/Dispatcher.h>
#include <Audio/Port.h>
#include <Jack/Server.h>
#include <Jack/Host.h>
#include <Jack/Port.h>

#include "AbstractIODropdown.h"


using std::vector;

using Audio::Port;


namespace Orza { namespace App { namespace Widget {


/**
 * Main class
 *
 */

class OutputDropdown : public AbstractIODropdown, public Util::Dispatcher {

    Q_OBJECT;


    public:

        OutputDropdown( QWidget * parent );
        explicit OutputDropdown( Jack::Server * );

        ~OutputDropdown() {};


        /**
         * Change events
         */

        static const char * CHANGE_EVENT;


        /**
         * Set Host
         */
        void setHost( Jack::Host * h ) {

            _Host = h;

        };


        /**
         * update connection
         */
        void updateOptions();

        /**
         * Add Port append order
         *
         * @param Port Port To be added
         *
         * @return bool
         */
        void addOutput( Jack::Port port ) {

            return addOutput( port, -1 );

        };


        /**
         * Add Port
         * will check for dups
         *
         * @param Port Port To be added
         * @param int order Position to be added
         *
         * @return bool
         */
        void addOutput( Jack::Port, const int );


        /**
         * Current jack port from index
         */

        const char * getCurrentJackPort();


        /**
         * has Port
         *
         * @return bool
         */
        //bool hasOutput( Port device );


    public slots:


        /**
         * Change event
         *
         */

        void handleSelectionChanged( int index );


    private:

        Jack::Host * _Host;

        vector<Jack::Port> _ports;

};

}; }; };
