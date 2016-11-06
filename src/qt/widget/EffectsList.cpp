/**
 * Effects List widget
 *
 */
#include <QList>
#include <vector>

#include <LADSPA/LADSPASearch.h>
#include <LADSPA/LADSPAPlugin.h>

#include "Effect.h"
#include "EffectsList.h"

using std::vector;

EffectsList::EffectsList() {

    Effect TestOption { "Test" };
    Effect TestOption2 { "Test2" };

    searcher = new LADSPASearch();

    vector<LADSPAPlugin> plugins = searcher->PluginSearch();

    for( vector<LADSPAPlugin>::iterator it= plugins.begin(); it != plugins.end(); ++it ) {

        //Effect opt { it->getName() };

        //addEffect( &opt );

    }

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
