/**
 * Effects List widget
 *
 */
#include <QList>

#include "Effect.h"
#include "EffectsList.h"

EffectsList::EffectsList() {

    Effect TestOption { "Test" };
    Effect TestOption2 { "Test2" };

    addEffect( &TestOption );
    addEffect( &TestOption2 );

}

EffectsList::EffectsList( QWidget * parent ) : QListWidget( parent ) {

}


/**
 * Add Effect implmentation
 * Will use list iterator
 *
 */
bool EffectsList::addEffect( Effect *Effect, const int order ) {

    //append( Effect->name );

    //Effects.insert( Effect );

    return true;

}
