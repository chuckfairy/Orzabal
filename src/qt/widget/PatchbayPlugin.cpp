/**
 * Patchbay plugin rack item
 */
#include "PatchbayPlugin.h"


namespace Orza { namespace App { namespace Widget {


PatchbayPlugin::PatchbayPlugin() :
    _WidgetContent( new QWidget() )
{

    _UI.setupUi( _WidgetContent );

};

void PatchbayPlugin::handleSelectChange( int index ) {

};

void PatchbayPlugin::handleRemoveClick() {

};

} } };
