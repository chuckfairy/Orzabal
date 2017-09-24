/**
 * Patchbay plugin rack item
 */
#include "PatchbayPlugin.h"


#include <LV2/Plugin.h>

#include <LV2/UIDriver.h>


using Orza::App::LV2UI::UIDriver;


namespace Orza { namespace App { namespace Widget {


/**
 * Test constructor
 */

PatchbayPlugin::PatchbayPlugin() :
    _WidgetContent( new QWidget() )
{

    _UI.setupUi( _WidgetContent );

};


/**
 * Construct from audio plugin
 */

PatchbayPlugin::PatchbayPlugin( Audio::Plugin * const p ) :
    _Plugin( p ),
    _WidgetContent( new QWidget() )
{

    _UI.setupUi( _WidgetContent );

    _UI.label->setText( _Plugin->getName() );

    //@TODO multi plugin useage
    LV2::Plugin * plugin = (LV2::Plugin*) _Plugin;

    UIDriver * driver = new UIDriver( plugin->getUI() );

    plugin->getUI()->addDriver( driver );

    _UI.scrollArea->setWidget( driver->getControlWidget() );


    //Event setting

    //View button

    connect(
        _UI.view_btn,
        SIGNAL( clicked() ),
        this,
        SLOT( handleViewClick() )
    );


    //Delete button

    connect(
        _UI.delete_btn,
        SIGNAL( clicked() ),
        this,
        SLOT( handleRemoveClick() )
    );

    connect(
        _UI.active_btn,
        SIGNAL( clicked() ),
        this,
        SLOT( handleActiveClick() )
    );

};


/**
 * Deletion
 */

PatchbayPlugin::~PatchbayPlugin() {

    delete _WidgetContent;

};


/**
 * Remove event char
 */

const char * PatchbayPlugin::REMOVE_EVENT = "REMOVE";
const char * PatchbayPlugin::ACTIVATE_EVENT = "ACTIVATION";


/**
 * Active methods
 */

void PatchbayPlugin::setActive() {

    if( ! _Plugin->isActive() ) {

        _Plugin->run();

    }

    _UI.active_btn->setStyleSheet( "color: #FFF " );

    _UI.active_btn->setText( "Active" );

    dispatch( ACTIVATE_EVENT, this );

};

void PatchbayPlugin::setInactive() {

    if( _Plugin->isActive() ) {

        _Plugin->pause();

    }

    _UI.active_btn->setStyleSheet( "color: #DEDEDE" );

    _UI.active_btn->setText( "Inactive" );

    dispatch( ACTIVATE_EVENT, this );

};

void PatchbayPlugin::toggleActive() {

    _Plugin->isActive()
        ? setInactive()
        : setActive();

};


/**
 * View toggle handler
 */

void PatchbayPlugin::handleViewClick() {

    _UI.scrollArea->isVisible()
        ?  _UI.scrollArea->hide()
        : _UI.scrollArea->show();

};


/**
 * Set inactive
 */

void PatchbayPlugin::handleActiveClick() {

    std::cout << "TEST\n";

    toggleActive();

};


/**
 * Remove click dispatch
 */

void PatchbayPlugin::handleRemoveClick() {

    dispatch( REMOVE_EVENT, this );

};

} } };
