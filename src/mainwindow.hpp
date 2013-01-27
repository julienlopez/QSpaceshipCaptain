#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui/QMainWindow>

#include <boost/shared_ptr.hpp>
class Ship;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    boost::shared_ptr<Ship> m_ship; //temp
};

#endif // MAINWINDOW_HPP
