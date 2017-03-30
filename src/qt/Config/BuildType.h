/**
 * Build type in config
 */
#pragma once

namespace Qrza { Qt { Config {

/**
 * Build types enum
 */

enum BuildType {
    Linux,
    Pi
};

BuildType CONFIG_BUILD = Pi;

} } };
