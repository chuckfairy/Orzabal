/**
 * LV2
 */

#include "WindowLayout.h"

#include <LV2/UI.h>
#include <LV2/Plugin.h>

#include <lilv/lilv.h>
#include <LV2/Port.h>

namespace Orza { namespace App { namespace LV2UI {

FlowLayout::FlowLayout(QWidget* parent, int margin, int hSpacing, int vSpacing)
    : QLayout(parent), m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::FlowLayout(int margin, int hSpacing, int vSpacing)
    : m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::~FlowLayout() {
    QLayoutItem* item;
    while ((item = takeAt(0))) {
        delete item;
    }
}

void FlowLayout::addItem(QLayoutItem* item) {
    itemList.append(item);
}

int FlowLayout::horizontalSpacing() const {
    if (m_hSpace >= 0) {
        return m_hSpace;
    } else {
        return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
    }
}

int FlowLayout::verticalSpacing() const {
    if (m_vSpace >= 0) {
        return m_vSpace;
    } else {
        return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
    }
}

int FlowLayout::count() const {
    return itemList.size();
}

QLayoutItem* FlowLayout::itemAt(int index) const {
    return itemList.value(index);
}

QLayoutItem* FlowLayout::takeAt(int index) {
    if (index >= 0 && index < itemList.size()) {
        return itemList.takeAt(index);
    } else {
        return 0;
    }
}

Qt::Orientations FlowLayout::expandingDirections() const {
    return 0;
}

bool FlowLayout::hasHeightForWidth() const {
    return true;
}

int FlowLayout::heightForWidth(int width) const {
    return doLayout(QRect(0, 0, width, 0), true);
}

void FlowLayout::setGeometry(const QRect &rect) {
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

QSize FlowLayout::sizeHint() const {
    return minimumSize();
}

QSize FlowLayout::minimumSize() const {
    QSize        size;
    QLayoutItem* item;
    foreach (item, itemList) {
        size = size.expandedTo(item->minimumSize());
    }

    return size + QSize(2 * margin(), 2 * margin());
}

int FlowLayout::doLayout(const QRect &rect, bool testOnly) const {
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);

    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int   x             = effectiveRect.x();
    int   y             = effectiveRect.y();
    int   lineHeight    = 0;

    QLayoutItem* item;
    foreach (item, itemList) {
        QWidget* wid = item->widget();

        int spaceX = horizontalSpacing();
        if (spaceX == -1) {
            spaceX = wid->style()->layoutSpacing(QSizePolicy::PushButton,
                    QSizePolicy::PushButton,
                    Qt::Horizontal);
        }
        int spaceY = verticalSpacing();
        if (spaceY == -1) {
            spaceY = wid->style()->layoutSpacing(QSizePolicy::PushButton,
                    QSizePolicy::PushButton,
                    Qt::Vertical);
        }

        int nextX = x + item->sizeHint().width() + spaceX;
        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0) {
            x          = effectiveRect.x();
            y          = y + lineHeight + spaceY;
            nextX      = x + item->sizeHint().width() + spaceX;
            lineHeight = 0;
        }

        if (!testOnly) {
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));
        }

        x          = nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
    }
    return y + lineHeight - rect.y() + bottom;
}

int FlowLayout::smartSpacing(QStyle::PixelMetric pm) const {
    QObject* parent = this->parent();
    if (!parent) {
        return -1;
    } else if (parent->isWidgetType()) {
        QWidget* pw = static_cast<QWidget*>(parent);
        return pw->style()->pixelMetric(pm, 0, pw);
    } else {
        return static_cast<QLayout*>(parent)->spacing();
    }
}

Control::Control(PortContainer portContainer, QWidget* parent)
    : QGroupBox(parent)
    , dial(new QDial())
    , plugin(portContainer.ui->getPlugin()->getLilvPlugin())
    , port(portContainer.port)
      , label(new QLabel())
{

    const LilvPort* lilvPort = port->lilv_port;
    LilvWorld* world = portContainer.ui->getPlugin()->getLilvWorld();

    LilvNode* rdfs_comment = lilv_new_uri(world, LILV_NS_RDFS "comment");

    setRange( port->controlRange[0], port->controlRange[1] );

    setValue( port->control );

    if( port->controlValueType == Audio::CONTROL_VALUE_INT
        || port->controlValueType == Audio::CONTROL_VALUE_ENUM
    ) {
        dial->setNotchesVisible( true );
    }


    // Fill layout
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(dial, 0, Qt::AlignHCenter);
    layout->addWidget(label, 0, Qt::AlignHCenter);
    setLayout(layout);

    setMinimumWidth( CONTROL_WIDTH );
    setMaximumWidth( CONTROL_WIDTH );

    LilvNode* nname = lilv_port_get_name(plugin, lilvPort);
    name = QString("%1").arg(lilv_node_as_string(nname));

    // Handle long names
    if (fontMetrics().width(name) > CONTROL_WIDTH) {
        setTitle(fontMetrics().elidedText(name, Qt::ElideRight, CONTROL_WIDTH));
    } else {
        setTitle(name);
    }

    // Set tooltip if comment is available
    LilvNode* comment = lilv_port_get(plugin, lilvPort, rdfs_comment);
    if (comment) {
        QString* tooltip = new QString();
        tooltip->append(lilv_node_as_string(comment));
        setToolTip(*tooltip);
    }

    setFlat(true);

    connect(dial, SIGNAL(valueChanged(int)), this, SLOT(dialChanged(int)));

    lilv_node_free(comment);

}

void Control::setValue(float value) {

    float step;

    if (port->controlValueType == Audio::CONTROL_VALUE_INT) {
        step = value;
    } else if (port->controlValueType == Audio::CONTROL_VALUE_ENUM) {
        step = (std::find(port->scalePoints.begin(), port->scalePoints.end(), value)
                - port->scalePoints.begin());
    } else if (port->controlValueType == Audio::CONTROL_VALUE_LOG) {
        step = port->steps * std::log(value / min) / log(max / min);
    } else {
        step = value * port->steps;
    }

    dial->setValue(step);
    label->setText(getValueLabel(value));
}

QString Control::getValueLabel(float value) {
    if (port->scaleMap[value]) {
        if (fontMetrics().width(port->scaleMap[value]) > CONTROL_WIDTH) {
            label->setToolTip(port->scaleMap[value]);
            return fontMetrics().elidedText(QString(port->scaleMap[value]),
                    Qt::ElideRight,
                    CONTROL_WIDTH);
        }
        return port->scaleMap[value];
    }

    return QString("%1").arg(value);
}

void Control::setRange(float minRange, float maxRange) {
    min = minRange;
    max = maxRange;

    if (port->controlValueType == Audio::CONTROL_VALUE_LOG) {
        minRange = 1;
        maxRange = port->steps;
    } else if (port->controlValueType == Audio::CONTROL_VALUE_ENUM) {
        minRange = 0;
        maxRange = port->scalePoints.size() - 1;
    } else if (port->controlValueType != Audio::CONTROL_VALUE_INT) {
        minRange *= port->steps;
        maxRange *= port->steps;
    }

    dial->setRange(minRange, maxRange);
}

float Control::getValue() {
    if (port->controlValueType == Audio::CONTROL_VALUE_ENUM) {
        return port->scalePoints[dial->value()];
    } else if (port->controlValueType == Audio::CONTROL_VALUE_INT) {
        return dial->value();
    } else if (port->controlValueType == Audio::CONTROL_VALUE_LOG) {
        return min * pow(max / min, (float)dial->value() / port->steps);
    } else {
        return (float)dial->value() / port->steps;
    }
}

void Control::dialChanged(int dialValue) {

    float value = getValue();

    label->setText(getValueLabel(value));
    port->control = value;

}

}; }; };
