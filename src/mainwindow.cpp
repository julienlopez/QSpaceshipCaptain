#include "mainwindow.hpp"
#include "shipdisplay.hpp"
#include "crewwidget.hpp"
#include "ship/ship.hpp"

#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>
#include <QApplication>
#include <QDir>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ShipDisplay* display = new ShipDisplay;


    QFile fichier(QDir(QApplication::applicationDirPath()).absoluteFilePath("ship.json"));
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

    QHBoxLayout* hl = new QHBoxLayout;
    CrewWidget* crewWidget = new CrewWidget;
    hl->addWidget(crewWidget);
    hl->addWidget(display);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(hl);

    for(Ship::type_list_crew::const_iterator i = m_ship->crewBegin(); i != m_ship->crewEnd(); ++i)
        crewWidget->addMember(*i);

    connect(display, SIGNAL(memberSelection(CrewMember)), crewWidget, SLOT(selectMember(CrewMember)));
    connect(crewWidget, SIGNAL(memberSelection(std::string)), display, SLOT(selectCrewMember(std::string)));
}

MainWindow::~MainWindow()
{}
