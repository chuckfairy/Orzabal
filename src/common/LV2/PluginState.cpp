/**
 * Plugin state usage on lv2 Plugin
 */
#include "Plugin.h"
#include "Preset.h"
#include "PluginState.h"

namespace LV2 {

/**
 * Main construct
 */

PluginState::PluginState( Plugin * plugin )
    : _Plugin( plugin )
{
};


/**
 * Main state setter
 */

void PluginState::applyLilvState() {

    const LV2_Feature * state_features = _Plugin->getLilvStateFeatures();

    bool must_pause = ! _safe_restore && _play_state == Audio::RUNNING;

    if( must_pause ) {

        _play_state = Audio::PAUSE_REQUESTED;

        _Plugin->pause();
        //zix_sem_wait(&paused);

        std::cout << "PAUSIN\n";
    }


    //Set state thread func to Plugin

    lilv_state_restore(
        _state,
        _Plugin->getLilvInstance(),
        Plugin::setPortValue,
        _Plugin,
        0,
        &state_features
    );


    if( must_pause ) {

        _Plugin->setRequestUpdate( true );
        _Plugin->run();

    }

    _play_state = Audio::RUNNING;

};


/**
 * State default setting
 */

void PluginState::setStateDefault() {

    _state = lilv_state_new_from_world(
        _Plugin->getLilvWorld(),
        _Plugin->getLV2Map(),
        lilv_plugin_get_uri( _Plugin->getLilvPlugin() )
    );

};


/**
 * Apply from preset
 */

void PluginState::setLilvState( Audio::Preset * preset ) {

    lilv_state_free( _state );

    Preset * lv2Preset = (LV2::Preset*) preset;

	lv2Preset->state = lilv_state_new_from_world(
        _Plugin->getLilvWorld(),
        _Plugin->getLV2Map(),
        lv2Preset->lilvPreset
    );

    _state = lv2Preset->state;

	applyLilvState();

};

};
