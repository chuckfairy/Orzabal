/**
 * Effects List widget
 *
 */
#pragma once

#include <map>

#include <QtCore>
#include <QListWidget>

#include "Effect.h"

using std::map;

class EffectsList : public QListWidget {

    private:

        /**
         * Effect struct list
         *
         */
        map<const char*, const Effect*> Effects;


    public:

        EffectsList();
        EffectsList( QWidget * parent );

        void setupUI();

        void update();

        void checkInstruments();

        void onChange();


        /**
         * Get instruments
         *
         * @return list<Effect*>
         *
         */
        map<const char*, const Effect*>* getEffects() {

            return &Effects;

        };


        /**
         * Add effect append order
         *
         * @param Effect instrument To be added
         *
         * @return bool
         */
        bool addEffect( Effect *effect ) {

            return addEffect( effect, -1 );

        };


        /**
         * Add effect
         *
         * @param Effect instrument To be added
         * @param int order Position to be added
         *
         * @return bool
         */
        bool addEffect( Effect *effect, const int order );


        /**
         * has Effect
         *
         * @return bool
         */
        bool hasEffect( Effect effect );

};
