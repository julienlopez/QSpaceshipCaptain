#include "powerwidget.hpp"

#include <QPainter>

PowerWidget::PowerWidget(QWidget *parent) :
    QWidget(parent)
{
    m_readOnly = false;

    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::black);
    setPalette(p);
    setAutoFillBackground(true);
}

uint8_t PowerWidget::value() const
{
    return m_value;
}

uint8_t PowerWidget::max() const
{
    return m_max;
}

bool PowerWidget::isReadOnly() const
{
    return m_readOnly;
}

void PowerWidget::setReadOnly(bool readOnly)
{
    m_readOnly = readOnly;
}

void PowerWidget::setValue(uint8_t value)
{
    m_value = value;
}

void PowerWidget::setMax(uint8_t max)
{
    m_max = max;
}

void PowerWidget::paintEvent(QPaintEvent* evt)
{
    Q_UNUSED(evt);
    QPainter p(this);
    p.save();
    QPen pen = p.pen();
    pen.setColor(Qt::lightGray);
    p.drawRect(rect());
    p.restore();
}

void PowerWidget::mousePressEvent(QMouseEvent* evt)
{

}
