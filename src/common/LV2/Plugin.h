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


    public:

        LV2Plugin();


}
