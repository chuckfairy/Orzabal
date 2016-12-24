/**
 * Qt gui of plugin window
 */
#pragma once

#include <QtCore>


namespace LV2 {

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
                int      margin   = -1,
                int      hSpacing = -1,
                int      vSpacing = -1);

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
