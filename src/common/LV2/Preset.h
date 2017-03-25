/**
 * Lilv plugin extension
 */
#pragma once

#include <lilv/lilv.h>

#include <Audio/Preset.h>

namespace LV2 {

struct Preset : public Audio::Preset {

    LilvState * state;

    const LilvNode * lilvPreset;

};

};
