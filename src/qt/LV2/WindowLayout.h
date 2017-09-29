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

#include <lv2/lv2plug.in/ns/ext/log/log.h>
#include <lv2/lv2plug.in/ns/ext/port-groups/port-groups.h>
#include <lv2/lv2plug.in/ns/ext/port-props/port-props.h>

#include <lilv/lilv.h>

#include <LV2/Port.h>
#include <LV2/UI.h>

#include "PortContainer.h"

#define CONTROL_WIDTH 150
#define DIAL_STEPS    10000

namespace Orza { namespace App { namespace LV2UI {

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
 * Controls GUI
 *
 */

class Control : public QGroupBox {

    Q_OBJECT

    public:
        Control(PortContainer portContainer, QWidget* parent = 0);

        Q_SLOT void dialChanged(int value);

        void setValue(float value);

        float getValue();

        QDial* dial;

    private:
        void    setRange(float min, float max);
        QString getValueLabel(float value);

        const LilvPlugin* plugin;
        struct LV2::Port* port;

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

}; }; };
