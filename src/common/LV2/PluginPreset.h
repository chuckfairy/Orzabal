/**
 * Plugin preset
 */
#pragma once

#include <vector>

#include <lilv/lilv.h>

#include <Audio/Preset.h>


using std::vector;


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

        /**
         * Plugin internal
         */

        Plugin * _Plugin;


        /**
         * Internal presets
         */

        vector<Audio::Preset*> _presets;

        Audio::Preset * _preset;


        /**
         * Lilv node types and setter
         */

        LilvNode * _rdfs_label;

        LilvNode * _pset_Preset;

        void setNodes();


    public:

        explicit PluginPreset( Plugin * );


        /**
         * Main setup
         */

        void setup();


        /**
         * Main getters setters
         */

        vector<Audio::Preset*> getAll();


        /**
         * Preset getter setters
         */

        void setPreset( Audio::Preset * preset ) {

            _preset = preset;

        };

        Audio::Preset * getPreset() {

            return _preset;

        };


        /**
         * Main apply to plugin state from current preset
         */

        void applyPreset();


        /**
         * Apply preset overload do setting as well
         */

        void applyPreset( Audio::Preset * );


        /**
         * Save current state as preset
         */

        void saveStateAsPreset();

};

};
