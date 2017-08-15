/**
 * Search for lv2
 *
 */
#pragma once

#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <lilv/lilv.h>

#include <Audio/Host.h>
#include <Audio/Plugin.h>
#include <Audio/Search.h>

#include "Plugin.h"

using std::vector;


namespace LV2 {


/**
 * Search extension
 */

class Search : public Audio::Search {

    private:

        LV2::Host * _Host;


    public:

        Search( Host * h );

        vector<Audio::Plugin*> findAll();

        void update();

};

};
