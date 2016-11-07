/**
 * Instrument dropdown / combobox widget
 *
 */
#pragma once

#include <map>

#include <QtCore>
#include <QComboBox>

#include "EffectOption.h"

using std::map;


/**
 * Effect dropdown GUI
 *
 */
class EffectDropdown : public QComboBox {

    private:

        /**
         * Effect struct list
         *
         */
        map<const char*, const EffectOption*> Effects;


    public:

        EffectDropdown( QWidget * parent );
        EffectDropdown();

        void setupUI();

        void update();

        void checkEffects();

        void onChange();


        /**
         * Get instruments
         *
         * @return list<EffectOption*>
         *
         */
        map<const char*, const EffectOption*>* getEffects() {

            return &Effects;

        };


        /**
         * Add instrument append order
         *
         * @param EffectOption instrument To be added
         *
         * @return bool
         */
        bool addEffect( EffectOption *instrument ) {

            return addEffect( instrument, -1 );

        };


        /**
         * Add instrument
         * will check for dups
         *
         * @param EffectOption instrument To be added
         * @param int order Position to be added
         *
         * @return bool
         */
        bool addEffect( EffectOption *instrument, const int order );


        /**
         * has instrument
         *
         * @return bool
         */
        bool hasEffect( EffectOption instrument );

};
