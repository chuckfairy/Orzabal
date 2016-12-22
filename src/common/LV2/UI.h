/**
 * Plugin UI
 *
 */
#pragma once

#include <lilv/lilv.h>
#include <suil/suil.h>
#include <sratom/sratom.h>

#include <Audio/UI.h>

#include "Plugin.h"


namespace LV2 {

/**
 * UI use of lilv
 *
 */
class UI : public Audio::UI {

    private:

        LilvUIs * _lilvUIS;

        const LilvUI * _lilvUI;

        const LilvNode * _uiType;

        bool _EXTERNAL_UI;

        LilvNode * getExternalKX();

        LilvNode * getExternalLV2();

        SuilHost * _uiSuil;

        Sratom * _uiSratom;

        void * _uiEventBuf;

    protected:

        LV2::Plugin * _Plugin;

    public:

        UI( Plugin * );

        void start();

        void stop();

        const char * getNativeUiType();

};

};
