/**
 * Preset dropdown
 */
#pragma once

#include <vector>

#include <QtCore>
#include <QComboBox>

#include <Audio/Port.h>
#include <Jack/Server.h>
#include <Jack/Host.h>
#include <Jack/Port.h>


using std::vector;

using Audio::Port;


//using Audio::Port;

namespace Orza { namespace App {  namespace Settings {

/**
 * Main class
 *
 */

class PresetDropdown : public QComboBox {

    Q_OBJECT


    public:

        PresetDropdown() {};
        ~PresetDropdown() {};


};

}; }; };
