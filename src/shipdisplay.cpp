#include "shipdisplay.hpp"
#include "ship/ship.hpp"
#include "pathinghelper.hpp"

#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

ShipDisplay::ShipDisplay(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(800, 800);
    setAutoFillBackground(true);
    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::black);
    setPalette(p);

    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(1000*s_dt);
    connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(updateShip()));
    m_updateTimer->start();
}

void ShipDisplay::setShip(wp_ship ship)
{
    m_ship = ship;
}

void ShipDisplay::mousePressEvent(QMouseEvent* evt)
{
    auto ship = m_ship.lock();
    if(!ship) return;

    QSize screenSize = size() - QSize(20, 20);
    double ratioX = ((double)screenSize.width()) / ship->width();
    double ratioY = ((double)screenSize.height()) / ship->height();
    double ratio = std::min(ratioX, ratioY);
    QPoint marge(width() - ratio*ship->width(), height() - ratio*ship->height());
    marge /= 2;
    QPointF pos = evt->posF() - marge;
    pos /= ratio;
    PointF posClick(pos.x(), pos.y());

    if(evt->button() == Qt::LeftButton) {
        for(Ship::type_list_crew::const_iterator i = ship->crewBegin(); i != ship->crewEnd(); ++i)
        {
            if((i->position()-posClick).dot() <= 0.2*0.2)
            {
                m_currentCrewMemberSelected = i->name();
                emit memberSelection(*i);
                update();
                return;
            }
        }
    } else if(evt->button() == Qt::RightButton) {
        try {
            CrewMember& cm = ship->memberByName(m_currentCrewMemberSelected);
            PointF start = cm.position();
            utils::type_list_points path = PathingHelper::simplePathFromTo(*ship, start, Point(posClick));
            cm.followPath(path);
        }
        catch(std::invalid_argument& ex)
        {}
    }
}

void ShipDisplay::paintEvent(QPaintEvent* evt)
{
    Q_UNUSED(evt);
    auto ship = m_ship.lock();
    if(!ship) return;
    QSize screenSize = size() - QSize(20, 20);
    double ratioX = ((double)screenSize.width()) / ship->width();
    double ratioY = ((double)screenSize.height()) / ship->height();
    double ratio = std::min(ratioX, ratioY);
    QPoint marge(width() - ratio*ship->width(), height() - ratio*ship->height());
    marge /= 2;

    QPainter p(this);
    p.translate(marge.x(), marge.y());
    p.scale(ratio, ratio);

    //drawing the ship
    p.save();
    p.setPen(Qt::lightGray);
    QPen pen = p.pen();
    pen.setWidthF(0.1);
    p.setPen(pen);
    p.setBrush(Qt::darkGray);
    p.drawRect(0,0, ship->width(), ship->height());
    p.restore();

    //drawing the rooms
    p.save();
    p.setPen(Qt::black);
    p.setBrush(Qt::white);
    for(Ship::type_list_rooms::const_iterator i = ship->roomsBegin(); i != ship->roomsEnd(); ++i)
    {
        drawRoom(p, *i);
    }
    p.restore();

    //drawing the doors
    p.save();
    p.setPen(Qt::cyan);
    pen = p.pen();
    pen.setWidthF(0.15);
    p.setPen(pen);
    for(Ship::type_list_doors::const_iterator i = ship->doorsBegin(); i != ship->doorsEnd(); ++i)
    {
        drawDoor(p, *i);
    }
    p.restore();

    //drawing the crew
    for(Ship::type_list_crew::const_iterator i = ship->crewBegin(); i != ship->crewEnd(); ++i)
    {
        if(i->name() == m_currentCrewMemberSelected)
        {
            p.save();
            p.setPen(Qt::red);
            drawCrew(p, *i);
            p.restore();
        }
        else
        {
            drawCrew(p, *i);
        }
    }
}

void ShipDisplay::selectCrewMember(const std::string& name)
{
    m_currentCrewMemberSelected = name;
    update();
}
void ShipDisplay::updateShip()
{
    auto ship = m_ship.lock();
    if(!ship) return;
    ship->update(s_dt);
    update();
}

void ShipDisplay::drawRoom(QPainter& p, const Room& room) const
{
    for(Room::type_list_coords::const_iterator j = room.squaresBegin(); j != room.squaresEnd(); ++j)
    {
        p.drawRect(j->x(), j->y(), 1, 1);
    }
    p.save();
    p.setBrush(Qt::NoBrush);
    p.setPen(Qt::black);
    QPen pen = p.pen();
    pen.setWidthF(0.1);
    p.setPen(pen);
    Room::type_list_coords walls = room.computeWalls();
    QPolygonF poly;
    for(Room::type_list_coords::const_iterator it = walls.begin(); it != walls.end(); ++it)
        poly.push_back(QPointF(it->x(), it->y()));
    p.drawPolygon(poly);
    p.restore();
}

void ShipDisplay::drawDoor(QPainter& p, const Door& room) const
{
    PointF from = room.from() + PointF(0.5, 0.5);
    PointF to = room.to() + PointF(0.5, 0.5);
    PointF centre = (from+to)/2;
    to.rotate(centre, Point::PI/2);
    from.rotate(centre, Point::PI/2);
    to = 0.4*(to-centre) + centre;
    from = 0.4*(from-centre) + centre;
    QLineF line(QPointF(from.x(), from.y()), QPointF(to.x(), to.y()));
    p.drawLine(line);
}

namespace {
QPointF toQPointF(const PointF& p)
{
    return QPointF(p.x(), p.y());
}
}

void ShipDisplay::drawCrew(QPainter& p, const CrewMember& crewMember) const
{
    p.drawEllipse(toQPointF(crewMember.position()), 0.2, 0.2);
}
