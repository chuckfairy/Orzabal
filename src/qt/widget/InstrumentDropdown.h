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

#include "InstrumentOption.h"

using std::vector;


/**
 * Instrument dropdown GUI
 *
 */
class InstrumentDropdown : public QComboBox {

    Q_OBJECT

    private:

        /**
         * Instrument struct list
         *
         */
        vector<const InstrumentOption*> Instruments;


        /**
         * LV2 searcher pointer
         */

        LV2::Search * Searcher;


        /**
         * Default select something
         *
         */

        InstrumentOption _placeholder { "-- Select Instrument --" };


    public:

        InstrumentDropdown( QWidget * parent );
        InstrumentDropdown();
        ~InstrumentDropdown() {};

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

        void handleSelectionChanged( int index ) {

            if( index == 0 ) { return; }

            QMessageBox* msg = new QMessageBox();
            msg->setWindowTitle("Hello !");
            msg->setText( currentText() );
            msg->show();

        };

};
