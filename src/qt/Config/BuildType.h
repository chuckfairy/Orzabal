/**
 * Build type in config
 */
#pragma once

namespace Orza { namespace App { namespace Config {

/**
 * Build types enum
 */

enum BuildType {
    Linux,
    Pi
};

static BuildType ORZA_BUILD_CONFIG = Pi;

} } };
