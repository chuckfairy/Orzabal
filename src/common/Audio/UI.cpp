/**
 * UI Impl
 */
#include "UIDriver.h"
#include "UI.h"

namespace Audio {

/**
 * Driver commands
 */

void UI::addDriver( UIDriver * driver ) {

    _drivers.push_back( driver );

};

void UI::addDrivers( vector<UIDriver*> drivers ) {

    vector<UIDriver*>::iterator it;

    for( it = drivers.begin(); it != drivers.end(); ++ it ) {

        addDriver( *it );

    }

};


/**
 * State driver methods
 */

void UI::startDrivers() {

    vector<UIDriver*>::iterator it;

    for( it = _drivers.begin(); it != _drivers.end(); ++ it ) {

        (*it)->start();

    }

};

void UI::stopDrivers() {

    vector<UIDriver*>::iterator it;

    for( it = _drivers.begin(); it != _drivers.end(); ++ it ) {

        (*it)->stop();

    }

};

void UI::updateDrivers() {

    vector<UIDriver*>::iterator it;

    for( it = _drivers.begin(); it != _drivers.end(); ++ it ) {

        (*it)->update();

    }

};

};
