#include "mainwindow.hpp"
#include "shipdisplay.hpp"

#include "ship/ship.hpp"

#include <QFile>
#include <QTextStream>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ShipDisplay* display = new ShipDisplay;
    setCentralWidget(display);

    QFile fichier("ship.json");
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier);
        QString ship = flux.readAll();
        m_ship.reset(new Ship(Ship::fromJson(ship.toStdString())));
        display->setShip(m_ship);
    }
    else {
        qDebug() << "impossible d'ouvrir le fichier";
    }
}

MainWindow::~MainWindow()
{
    
}
