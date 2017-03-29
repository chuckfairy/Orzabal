/**
 * Qt gui of plugin window
 */
#pragma once

#include <cmath>

#include <QAction>
#include <QApplication>
#include <QDial>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QScrollArea>
#include <QStyle>
#include <QTimer>
#include <QWidget>
#include <QWindow>

#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/atom/forge.h>
#include <lv2/lv2plug.in/ns/ext/buf-size/buf-size.h>
#include <lv2/lv2plug.in/ns/ext/data-access/data-access.h>
#include <lv2/lv2plug.in/ns/ext/event/event.h>
#include <lv2/lv2plug.in/ns/ext/log/log.h>
#include <lv2/lv2plug.in/ns/ext/midi/midi.h>
#include <lv2/lv2plug.in/ns/ext/options/options.h>
#include <lv2/lv2plug.in/ns/ext/parameters/parameters.h>
#include <lv2/lv2plug.in/ns/ext/patch/patch.h>
#include <lv2/lv2plug.in/ns/ext/port-groups/port-groups.h>
#include <lv2/lv2plug.in/ns/ext/port-props/port-props.h>
#include <lv2/lv2plug.in/ns/ext/presets/presets.h>
#include <lv2/lv2plug.in/ns/ext/resize-port/resize-port.h>
#include <lv2/lv2plug.in/ns/ext/state/state.h>
#include <lv2/lv2plug.in/ns/ext/time/time.h>
#include <lv2/lv2plug.in/ns/ext/uri-map/uri-map.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/worker/worker.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

#include <lilv/lilv.h>

#define CONTROL_WIDTH 150
#define DIAL_STEPS    10000

namespace LV2 {


/**
 * Forwarding
 */

class PortContainer;


/**
 * Layout of plugin
 */

class FlowLayout : public QLayout {

    private:

        int doLayout(const QRect &rect, bool testOnly) const;
        int smartSpacing(QStyle::PixelMetric pm) const;

        QList<QLayoutItem*> itemList;
        int m_hSpace;
        int m_vSpace;


    public:

        FlowLayout(QWidget* parent,
                int margin   = -1,
                int hSpacing = -1,
                int vSpacing = -1);

        FlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);

        ~FlowLayout();

        void addItem(QLayoutItem* item);

        int horizontalSpacing() const;

        int verticalSpacing() const;

        Qt::Orientations expandingDirections() const;

        bool hasHeightForWidth() const;

        int heightForWidth(int) const;

        int count() const;

        QLayoutItem* itemAt(int index) const;

        QSize minimumSize() const;

        void setGeometry(const QRect &rect);

        QSize sizeHint() const;

        QLayoutItem * takeAt(int index);

};


/**
 * Qt preset
 *
 */

//class PresetAction : public QAction {

    //Q_OBJECT

    //public:

        //PresetAction(QObject* parent, Jalv* jalv, LilvNode* preset)
            //: QAction(parent)
    //{
        //connect(this, SIGNAL(triggered()),
                //this, SLOT(presetChosen()));
    //}

        //Q_SLOT void presetChosen() {
            //jalv_apply_preset(_jalv, _preset);
        //}

    //private:

        //Jalv*     _jalv;
        //LilvNode* _preset;
//};


/**
 * Controls GUI
 *
 */

class Control : public QGroupBox {

    Q_OBJECT

    public:
        Control(PortContainer portContainer, QWidget* parent = 0);

        Q_SLOT void dialChanged(int value);

        void setValue(float value);

        QDial* dial;

    private:
        void    setRange(float min, float max);
        QString getValueLabel(float value);
        float   getValue();

        const LilvPlugin* plugin;
        struct Port*      port;

        QLabel* label;
        QString name;
        int     steps;
        float   max;
        float   min;
        bool    isInteger;
        bool    isEnum;
        bool    isLogarithmic;

        std::vector<float>           scalePoints;
        std::map<float, const char*> scaleMap;
};

};
