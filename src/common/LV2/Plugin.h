/**
 * LV2 Plugin
 *
 */
#pragma once

#include <string.h>

#include <lilv/lilv.h>

#include <Audio/Plugin.h>


class LV2Plugin : public Plugin {

    private:

        const LilvPlugin *  _lilvPlugin;

        void setLilvPlugin();

    protected:

        const char * TYPE = "LV2";


    public:

        LV2Plugin();

        LV2Plugin( const LilvPlugin* p );

        //LV2Plugin( LilvPluginImpl const* p ) {};

        Port createPort( long portNum );

        void setPorts();

        void setLilvPlugin( const LilvPlugin* p );

};
