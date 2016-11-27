/**
 * Instrument dropdown / combobox widget
 *
 */
#pragma once

#include <map>

#include <QtCore>
#include <QComboBox>

#include <LV2/Search.h>

#include "InstrumentOption.h"

using std::map;


/**
 * Instrument dropdown GUI
 *
 */
class InstrumentDropdown : public QComboBox {

    private:

        /**
         * Instrument struct list
         *
         */
        map<const char*, const InstrumentOption*> Instruments;


        /**
         * LV2 searcher pointer
         */

        LV2Search * Searcher;

    public:

        InstrumentDropdown( QWidget * parent );
        InstrumentDropdown();

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
        map<const char*, const InstrumentOption*>* getInstruments() {

            return &Instruments;

        };


        /**
         * Add instrument append order
         *
         * @param InstrumentOption instrument To be added
         *
         * @return bool
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
         * @return bool
         */
        bool addInstrument( InstrumentOption *instrument, const int order );


        /**
         * has instrument
         *
         * @return bool
         */
        bool hasInstrument( InstrumentOption instrument );

};
