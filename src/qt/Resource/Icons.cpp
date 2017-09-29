/**
 * Qt awesome icon resource
 */
#include <stdexcept>

#include "Icons.h"

namespace Orza { namespace App { namespace Resource {

QtAwesome * Icons::AWESOME = nullptr;

QtAwesome * Icons::getResource() {

    if( AWESOME == nullptr ) {

        throw std::runtime_error(
            "Application not set for qt awesome"
        );

    }

    return AWESOME;

};

void Icons::setResource( QApplication * app ) {

    AWESOME = new QtAwesome( app );
    AWESOME->initFontAwesome();

    AWESOME->setDefaultOption( "color", QColor( 255, 255, 255 ) );
    AWESOME->setDefaultOption( "color-disabled", QColor(70,70,70,60));
    AWESOME->setDefaultOption( "color-active", QColor( 255, 255, 255 ) );
    AWESOME->setDefaultOption( "color-selected", QColor( 255, 255, 255 ) );
    //AWESOME->setDefaultOption( "scale-factor", 1.3 );

};


/**
 * Get icon from int character
 */

QIcon Icons::getIcon( int character ) {

    return getResource()->icon( character );

};

QFont Icons::getFont( int size ) {

    return getResource()->font( size );

};

}; }; };
