/**
 * LV2 Plugin
 *
 */
#pragma once

#include <iostream>
#include <string.h>

#include <lilv/lilv.h>

#include <Audio/Plugin.h>


class LV2Plugin : public Plugin {

    private:

        const LilvPlugin *  _lilvPlugin;

        void setLilvPlugin();

        char _lilvURI[500];

    protected:

        const char * TYPE = "LV2";


    public:

        LV2Plugin();

        LV2Plugin( const LilvPlugin* p );

        Port createPort( long portNum );

        void setPorts();

        void setLilvPlugin( const LilvPlugin* p );

        void start();

};
