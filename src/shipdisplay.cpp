#include "shipdisplay.hpp"
#include "ship/ship.hpp"

#include <QPainter>

ShipDisplay::ShipDisplay(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(400,400);
    setAutoFillBackground(true);
    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::black);
    setPalette(p);
}

void ShipDisplay::setShip(wp_ship ship)
{
    m_ship = ship;
}

void ShipDisplay::paintEvent(QPaintEvent* evt)
{
    Q_UNUSED(evt);
    boost::shared_ptr<Ship> ship = m_ship.lock();
    if(!ship) return;
    QSize screenSize = size() - QSize(20, 20);
    double ratioX = ((double)screenSize.width()) / ship->width();
    double ratioY = ((double)screenSize.height()) / ship->height();
    double ratio = std::min(ratioX, ratioY);
    QPoint marge(width() - ratio*ship->width(), height() - ratio*ship->height());
    marge /= 2;

    QPainter p(this);
    p.setPen(Qt::lightGray);
    p.translate(marge.x(), marge.y());
    p.scale(ratio, ratio);
    p.drawRect(0,0, ship->width(), ship->height());
}
