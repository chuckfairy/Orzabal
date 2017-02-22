/**
 * Instrument dropdown / combobox widget
 *
 */
#pragma once

#include <map>
#include <vector>
#include <iostream>

#include <QtCore>
#include <QtGui>
#include <QComboBox>
#include <QMessageBox>

#include <LV2/Search.h>
#include <Audio/Plugin.h>
#include <Util/Dispatcher.h>
#include <Jack/Server.h>

#include "InstrumentOption.h"

using std::vector;


/**
 * Instrument dropdown GUI
 *
 */

class InstrumentDropdown :
    public QComboBox,
    public Util::Dispatcher
{

    Q_OBJECT

    private:

        /**
         * Instrument struct list
         *
         */
        vector<const InstrumentOption*> Instruments;


        /**
         * Jack server
         */

        Jack::Server * _Server;


        /**
         * Default select something
         *
         */

        InstrumentOption _placeholder { "-- Select Instrument --" };


    public:

        InstrumentDropdown( QWidget * parent );
        InstrumentDropdown( Jack::Server * );
        ~InstrumentDropdown() {};

        /**
         * Events
         */

        static const char * CHANGE_EVENT;


        /**
         * Main ui
         */

        void setupUI();

        void update();

        void checkInstruments();

        void onChange();


        /**
         * Get instruments
         *
         * @return list<InstrumentOption*>
         *
         */
        vector<const InstrumentOption*>* getInstruments() {

            return &Instruments;

        };


        /**
         * Add instrument append order
         *
         * @param InstrumentOption instrument To be added
         *
         */
        bool addInstrument( InstrumentOption *instrument ) {

            return addInstrument( instrument, -1 );

        };


        /**
         * Add instrument
         * will check for dups
         *
         * @param InstrumentOption instrument To be added
         * @param int order Position to be added
         *
         */
        bool addInstrument( InstrumentOption *instrument, const int order );


        /**
         * has instrument
         *
         */
        bool hasInstrument( InstrumentOption instrument );


    public slots:


        /**
         * Change event
         *
         */

        void handleSelectionChanged( int index );

};
