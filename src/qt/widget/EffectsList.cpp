/**
 * Effects List widget
 *
 */
#include <QList>
#include <vector>

#include "Effect.h"
#include "EffectsList.h"

using std::vector;

EffectsList::EffectsList() {

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
