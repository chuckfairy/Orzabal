/**
 * Plugin preset
 */
#pragma once

#include <Audio/Preset.h>


namespace LV2 {

/**
 * Forwarding
 */

class Plugin;


/**
 * Main class
 */

class PluginPreset {

    private:

        Plugin * _Plugin;

        /**
         * Interal presets
         */

        vector<Audio::Preset*> _presets;

        Audio::Preset * _preset;

    public:

        explicit PluginPreset( Plugin * );


        /**
         * Main getters setters
         */

        vector<Audio::Preset*> getAll();

        void setPreset( Preset * );

};

};
