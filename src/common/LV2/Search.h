/**
 * Search for lv2
 *
 */
#pragma once

#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include <Audio/Host.h>
#include <Audio/Plugin.h>
#include <Audio/Search.h>

using std::vector;


namespace LV2 {


/**
 * Search extension
 */

class Search : public Audio::Search {

    public:

        Search();

        vector<Audio::Plugin*> findAll();

        void update();


    private:

};

};
