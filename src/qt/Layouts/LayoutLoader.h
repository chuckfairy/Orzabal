/**
 * Qt layout loader
 */
#pragma once

#include <Util/Repository.h>

#include <stdexcept>

#include <json/json.hpp>

#include "LayoutRepository.h"

#include "Layout.h"

#include <Audio/PatchbayPresetLoader.h>

using nlohmann::json;

class MainWindow;

namespace Orza { namespace App { namespace Layouts {

class LayoutLoader : public Audio::PatchbayPresetLoader {

    public:

        LayoutLoader( MainWindow * );
        ~LayoutLoader() {};


        /**
         * Virtuals
         */

        void load( json * );

        void loadLayout( const char * type );

        void loadLayout( Layout * );


        /**
         * Getters
         */

        Layout * getCurrent() {

            return _CurrentLayout;

        };


    private:

        MainWindow * _App;

        Layout * _CurrentLayout;

        LayoutRepository _Repo;

};

}; }; };
