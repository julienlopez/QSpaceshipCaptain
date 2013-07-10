#include "powerhandlingwidget.hpp"
#include "powerwidget.hpp"

#include <QHBoxLayout>

PowerHandlingWidget::PowerHandlingWidget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout* hl = new QHBoxLayout;

    PowerWidget* pw = new PowerWidget;
    pw->setMax(20);
    pw->setValue(5);
    pw->setReadOnly(true);
    hl->addWidget(pw);

    pw = new PowerWidget;
    pw->setMax(5);
    pw->setValue(1);
    hl->addWidget(pw);

    pw = new PowerWidget;
    pw->setMax(5);
    pw->setValue(0);
    hl->addWidget(pw);

    pw = new PowerWidget;
    pw->setMax(5);
    pw->setValue(4);
    hl->addWidget(pw);

    setLayout(hl);

    setMinimumSize(200, 200);
}
