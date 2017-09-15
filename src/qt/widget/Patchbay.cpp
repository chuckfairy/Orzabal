/**
 * Patchbay tab UI impl
 */
#include <MainWindow.h>

#include <Jack/Patchbay.h>
#include <Jack/PatchbayEffects.h>

#include "Events/RemoveClickEvent.h"
#include "Events/ActivateClickEvent.h"
#include "PatchbayPlugin.h"
#include "Patchbay.h"


namespace Orza { namespace App { namespace Widget {

Patchbay::Patchbay( MainWindow * app ) :
    _App( app ),
    _WidgetContent( new QWidget() ),
    _LayoutWidget( new QWidget() ),
    _Dropdown( new EffectDropdown( app->getPluginSearch() ) )
{

    _UI.setupUi( _WidgetContent );

    _UI.horizontalLayout->insertWidget( 0, _Dropdown );

    app->getUI()->tabWidget->insertTab( 1, _WidgetContent, "Effects" );

    _Layout = new QGridLayout;

    _LayoutWidget->setLayout( _Layout );

    _UI.scrollArea->setWidget( _LayoutWidget );

    connect(
        _UI.pushButton,
        SIGNAL( clicked() ),
        this,
        SLOT( handleAddClick() )
   );

};


/**
 * Add click handle and add plugin
 */

void Patchbay::handleAddClick() {

    std::cout << "ADD CLICK\n";

    int index = _Dropdown->currentIndex();

    if ( index == 0 ) { return; }


    //Create patchbay plugin ui

    Audio::Plugin * p = _Dropdown->getCurrentPlugin()->clone();

    addPlugin( p );

};


/**
 * Add plugin
 */

void Patchbay::addPlugin( Audio::Plugin * p ) {

    Jack::Patchbay * h = _App->getServer()->getPatchbay();

    h->getEffects()->addEffect( p );

    PatchbayPlugin * plugin = new PatchbayPlugin( p );

    _plugins.push_back( plugin );

    _Layout->addWidget( plugin->getWidget() );


    //Set plugin events

    Util::Event * e = new RemoveClickEvent<Patchbay, PatchbayPlugin>( this );
    Util::Event * activeEvent = new ActivateClickEvent<Patchbay, PatchbayPlugin>( this );

    plugin->on( PatchbayPlugin::REMOVE_EVENT, e );
    plugin->on( PatchbayPlugin::ACTIVATE_EVENT, activeEvent );

};


/**
 * Remove plugin
 */

void Patchbay::removePlugin( PatchbayPlugin * plugin ) {

    Jack::Patchbay * h = _App->getServer()->getPatchbay();

    h->getEffects()->removeEffect( plugin->getPlugin() );

    delete plugin;

};


/**
 * Event handlers
 */

void Patchbay::handleRemoveClick( PatchbayPlugin * plugin ) {

    removePlugin( plugin );

};

void Patchbay::handleActivateClick( PatchbayPlugin * plugin ) {

    Jack::Patchbay * h = _App->getServer()->getPatchbay();

    h->getEffects()->connectEffectPorts();

};


/**
 * Clear all plugins
 */

void Patchbay::clearPlugins() {

    vector<PatchbayPlugin*>::iterator it;

    for( it = _plugins.begin(); it != _plugins.end(); ++ it ) {

        removePlugin( (*it) );

    }

}



} } };
