/**
 * Instrument dropdown / combobox widget
 *
 */
#pragma once

#include <list>

#include <QtCore>
#include <QComboBox>

#include "InstrumentOption.h"

using std::list;


/**
 * Instrument dropdown GUI
 *
 */
class InstrumentDropdown : public QComboBox {

    private:

        list<InstrumentOption> Instruments;


    public:

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
        list<InstrumentOption>* getInstruments() {

            return &Instruments;

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
        bool addInstrument( InstrumentOption instrument, const int order );


        /**
         * has instrument
         *
         * @return bool
         */
        bool hasInstrument( InstrumentOption instrument );

};
