/**
 * Output jack device dropdown
 *
 */
#pragma once


#include <vector>

#include <QtCore>
#include <QComboBox>

#include <Server/JackServer.h>
#include <Audio/Jack.h>
#include <Audio/Port.h>


using std::vector;


//using Audio::Port;


/**
 * Main class
 *
 */

class OutputDropdown : public QComboBox {

    private:

        Audio::Jack * _Host;


    public:

        OutputDropdown( QWidget * parent );
        OutputDropdown( JackServer * );


        /**
         * Set Host
         */
        void setHost( Audio::Jack * h ) {

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
        void addOutput( Port port ) {

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
        void addOutput( Port, const int );


        /**
         * has Port
         *
         * @return bool
         */
        //bool hasOutput( Port device );

};
