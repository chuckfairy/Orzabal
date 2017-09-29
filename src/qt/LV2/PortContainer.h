/**
 * Port container
 */
#pragma once

#include <LV2/UI.h>
#include <LV2/Port.h>

namespace Orza { namespace App { namespace LV2UI {

/**
 * Forward
 */
class Control;

struct PortContainer {
    LV2::UI * ui;
    LV2::Port * port;
    Control * controlWidget;
};

}; }; };
