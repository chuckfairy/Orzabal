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

        Audio::PlayState _play_state = Audio::PAUSED;


        /**
         * Lilv state
         */

        LilvState * _state;


    public:

        explicit PluginState( Plugin * );


        /**
         * Play state setters getters
         */

        Audio::PlayState getPlayState() {

            return _play_state;

        };

        void setPlayState( Audio::PlayState state ) {

            _play_state = state;

        };


        /**
         * State safe restore
         *
         */

        bool getSafeRestore() {

            return _safe_restore;

        };

        void setSafeRestore( bool restore ) {

            _safe_restore = restore;

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
