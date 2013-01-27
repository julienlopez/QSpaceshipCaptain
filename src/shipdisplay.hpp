#ifndef SHIPDISPLAY_HPP
#define SHIPDISPLAY_HPP

#include <boost/weak_ptr.hpp>

#include <QWidget>

class Ship;

class ShipDisplay : public QWidget
{
    Q_OBJECT

public:
    typedef boost::weak_ptr<Ship> wp_ship;

    explicit ShipDisplay(QWidget *parent = 0);

    void setShip(wp_ship ship);
    
protected:
    void paintEvent(QPaintEvent* evt);

signals:
    
public slots:

private:
    wp_ship m_ship;
    
};

#endif // SHIPDISPLAY_HPP
