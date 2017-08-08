/**
 * Qt layout loader
 */
#pragma once

#include <stdexcept>

#include <json/json.hpp>

#include <Audio/PatchbayPresetLoader.h>

using nlohmann::json;


namespace Orza { namespace App { namespace Layout {

class LayoutLoader : public Audio::PatchbayPresetLoader {

    LayoutLoader() {};
    ~LayoutLoader() {};


    /**
     * Virtuals
     */

    void load( json * );

};

}; }; };
