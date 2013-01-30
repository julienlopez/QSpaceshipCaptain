#ifndef TESTROOM_HPP
#define TESTROOM_HPP

#include <QObject>

class TestRoom : public QObject
{
    Q_OBJECT
public:
    explicit TestRoom(QObject *parent = 0);

private slots:
    
};

#endif // TESTROOM_HPP
