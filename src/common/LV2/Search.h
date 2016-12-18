/**
 * Search for lv2
 *
 */
#pragma once

#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include <Audio/Plugin.h>

#include <Audio/Search.h>

#include <lilv/lilv.h>

#include "Plugin.h"

using std::vector;

namespace LV2 {

class Search : public Audio::Search {

    public:

        Search();

        vector<Audio::Plugin*> findAll();

};

};
