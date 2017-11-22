/**
 * Patchbay plugin rack item
 */
#include "PatchbayPlugin.h"

#include <Resource/Icons.h>

#include <LV2/Plugin.h>

#include <LV2/UIDriver.h>


using Orza::App::LV2UI::UIDriver;
using Orza::App::Resource::Icons;


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

PatchbayPlugin::PatchbayPlugin( Jack::Server * s, Audio::Plugin * const p ) :
    _Server( s ),
    _Plugin( p ),
    _WidgetContent( new QWidget() )
{

    _UI.setupUi( _WidgetContent );

    //Font
    QFont iconFont = Icons::getFont( 20 );

    //Button setup

    _UI.active_btn->setFont( iconFont );
    setActive();

    _UI.view_btn->setFont( iconFont );
    _UI.view_btn->setText( QChar( fa::eye ) );

    _UI.delete_btn->setFont( iconFont );
    _UI.delete_btn->setText( QChar( fa::trash ) );


    //Label setup

    _UI.label->setText( _Plugin->getName() );


    //@TODO multi plugin useage
    LV2::Plugin * plugin = (LV2::Plugin*) _Plugin;

    UIDriver * driver = new UIDriver( _Server, plugin->getUI() );

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

    _UI.active_btn->setText( QChar( fa::microphone ) );

    dispatch( ACTIVATE_EVENT, this );

};

void PatchbayPlugin::setInactive() {

    if( _Plugin->isActive() ) {

        _Plugin->pause();

    }

    _UI.active_btn->setStyleSheet( "color: #AAA" );

    _UI.active_btn->setText( QChar( fa::microphoneslash ) );

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

    if( _UI.scrollArea->isVisible() ) {

        _UI.scrollArea->hide();

        _UI.view_btn->setStyleSheet( "color: #AAA" );

        _UI.view_btn->setText( QChar( fa::eyeslash ) );

    } else {

        _UI.scrollArea->show();

        _UI.view_btn->setStyleSheet( "color: #FFF" );

        _UI.view_btn->setText( QChar( fa::eye ) );

    }

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
