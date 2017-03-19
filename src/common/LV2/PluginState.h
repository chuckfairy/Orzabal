/**
 * Plugin state usage
 */
#pragma once

#include <lilv/lilv.h>

#include <Audio/PlayState.h>
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


        /**
         * Lilv state
         */

        LilvState * _state;

    public:

        explicit PluginState( Plugin * );


        /**
         * State enums
         */

        Audio::PlayState getPlayState() {

            return _play_state;

        };


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


        /**
         * Main apply of state
         */

        void applyLilvState();

};

};
