/**
 * Preset action item
 */
#pragma once

namespace LV2 {

/**
 * Forwarding
 */

class UI;


/**
 * Main class
 */

class PresetAction : public QAction {

    Q_OBJECT

    private:

        UI * _UI;
        LilvNode * _preset;

    public:

        PresetAction( QObject * parent, UI *, LilvNode * );
            QAction(parent),
            _jalv(jalv),
            _preset(preset)
        {
            connect(
                this,
                SIGNAL(triggered()),
                this,
                SLOT(presetChosen())
            );
        }

        Q_SLOT void presetChosen() {
            jalv_apply_preset(_jalv, _preset);
        }

};

};
