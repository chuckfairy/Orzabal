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

PatchbayPlugin::PatchbayPlugin( Audio::Plugin * p ) :
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

    connect(
        _UI.view_btn,
        SIGNAL( clicked() ),
        this,
        SLOT( handleViewClick() )
   );

};

void PatchbayPlugin::handleViewClick() {

    _UI.scrollArea->isVisible()
        ?  _UI.scrollArea->hide()
        : _UI.scrollArea->show();

};

void PatchbayPlugin::handleRemoveClick() {

};

} } };
