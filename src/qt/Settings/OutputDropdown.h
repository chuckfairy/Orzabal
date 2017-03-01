/**
 * Output jack device dropdown
 *
 */
#pragma once


#include <vector>

#include <QtCore>
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

class OutputDropdown : public QComboBox, public Util::Event {

    private:

        Jack::Host * _Host;


    public:

        OutputDropdown( QWidget * parent );
        OutputDropdown( Jack::Server * );


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

};
