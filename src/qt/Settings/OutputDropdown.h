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


using std::vector;

using Audio::Port;


//using Audio::Port;


/**
 * Main class
 *
 */

class OutputDropdown : public QComboBox, public Util::Dispatcher {

    Q_OBJECT

    private:

        Jack::Host * _Host;


    public:

        OutputDropdown( QWidget * parent );
        explicit OutputDropdown( Jack::Server * );

        virtual ~OutputDropdown() {};


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

};
