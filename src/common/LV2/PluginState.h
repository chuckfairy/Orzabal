/**
 * Plugin state usage
 */
#pragma once

#include <lilv/lilv.h>

#include <Audio/Preset.h>

namespace LV2 {

/**
 * Class forwarding
 */

class Plugin;


/**
 * Main class
 */

class PluginState {

    private:

        /**
         * Plugin internal
         */

        Plugin * _Plugin;

        bool STATE_SET = false;


        /**
         * State internals
         */

        bool _safe_restore = false;

        Audio::PlayState _play_state;

        void applyLilvState();


        /**
         * Lilv state
         */

        LilvState * _state;

    public:

        explicit PluginState( Plugin * );


        /**
         * State getters
         */

        LilvState * getLilvState() {

            return _state;

        };


        /**
         * State setting
         */

        void setStateDefault();

        void setLilvState( LilvState * );

        void setLilvState( Audio::Preset * );

};

};
