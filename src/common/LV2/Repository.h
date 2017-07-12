/**
 * Repo manager of plugins
 */
#pragma once

#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <lilv/lilv.h>

#include <Audio/Plugin.h>
#include <Util/Repository.h>

using std::vector;


namespace LV2 {


/**
 * Search extension
 */

class Repository : Util::Repository<Audio::Plugin> {

    private:

        LV2::Host * _Host;


    public:

        explicit Repository( Host * h );

        vector<Audio::Plugin*> findAll();

        /**
         * manevour
         */

        void update();


        /**
         * Extra repo finds
         */

        bool hasByURI( const char * );

};

};
