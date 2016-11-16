/**
 * LV2 Plugin
 *
 */
#pragma once

#include <Plugin.h>

#include <string.h>

#include <lilv/lilv.h>

class LV2Plugin : public Plugin {

    protected:

        char[10] TYPE = "LV2";

        const LilvPlugin * _lilvPlugin;


    public:

        LV2Plugin();

};
