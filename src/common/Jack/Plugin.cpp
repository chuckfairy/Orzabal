/**
 * LV2 Plugin
 *
 */
#include "Plugin.h"


namespace Jack {

/**
 * Plugin Main fro Audio::Plugin
 */

const char * Plugin::TYPE = "JACK";

const char * Plugin::getType() {

    return Plugin::TYPE;

};

};
