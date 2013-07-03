#ifndef SHIPDISPLAY_HPP
#define SHIPDISPLAY_HPP

#include <memory>

#include <QWidget>

class Ship;
class Room;
class Door;
class CrewMember;

class ShipDisplay : public QWidget
{
    Q_OBJECT

public:
    typedef std::weak_ptr<Ship> wp_ship;

    explicit ShipDisplay(QWidget *parent = 0);

    void setShip(wp_ship ship);
    
protected:
    void mousePressEvent(QMouseEvent* evt);
    void paintEvent(QPaintEvent* evt);

signals:
    void memberSelection(const CrewMember& crewMember);

public slots:
    void selectCrewMember(const std::string& name);
    void updateShip();

private:
    wp_ship m_ship;
    std::string m_currentCrewMemberSelected;
    QTimer* m_updateTimer;

    static void drawRoom(QPainter& p, const Room& room);
    static void drawDoor(QPainter& p, const Door& room);
    static void drawCrew(QPainter& p, const CrewMember& crewMember, const std::string& currentCrewMemberSelected);

    static constexpr double s_dt = .1;
    
};

#endif // SHIPDISPLAY_HPP
