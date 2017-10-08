/**
 * Pin repo class
 */
#include <string>
#include <vector>

#include "Config/Defaults.h"

#include <json/json.hpp>

#include "Pin.h"

#include "PinRepository.h"

using std::string;
using std::vector;

using nlohmann::json;


namespace Orza { namespace Pi {

/**
 * Construct
 */

PinRepository::PinRepository() {};


/**
 * Iterator methods
 */

void PinRepository::setup() {

    vector<Pin*>::iterator it;

    vector<Pin*> items = this->getAll();

    for( it = items.begin(); it != items.end(); ++ it ) {

        (*it)->setup();

    }

};

void PinRepository::update() {

    vector<Pin*>::iterator it;

    vector<Pin*> items = this->getAll();

    for( it = items.begin(); it != items.end(); ++ it ) {

        (*it)->update();

    }

};


/**
 * Statics
 */

PinRepository PinRepository::loadFromDefaultConfig() {

    PinRepository repo;

    json j = Config::DEFAULT_PIN_LAYOUT;

    if( j["pins"].empty() ) {

        return repo;

    }

    for( json::iterator it = j["pins"].begin(); it != j["pins"].end(); ++it ) {

        json pinJSON = (*it);

        PinType type = TYPE_LED;;

        string vs = pinJSON["pin_type"].get<string>();

        std::cout << vs.c_str()[0] << "\n";

        switch( vs.c_str()[0] ) {

            case 'L':
                type = TYPE_LED;
                break;

            case 'R':
                type = TYPE_RESTART;
                break;

            case 'S':
                type = TYPE_SHUTDOWN;
                break;

        }

        std::cout << type << "\n";

        Pin * p = new Pin( type, pinJSON["pin"].get<int>() );

        repo.add( p );

    }

    return repo;

};

}; };
