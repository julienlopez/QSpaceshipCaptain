#include "crewmemberwidget.hpp"
#include <ship/crewmember.hpp>

#include <QVBoxLayout>
#include <QLabel>

CrewMemberWidget::CrewMemberWidget(const CrewMember& cm, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* vl = new QVBoxLayout;
    m_labelId = new QLabel(QString::fromStdString(cm.name()));
    vl->addWidget(m_labelId);
    setLayout(vl);
    setStyleSheet("margin: 10px;");
}

QLabel* CrewMemberWidget::labelId() const
{
    return m_labelId;
}

void CrewMemberWidget::select()
{
    QPalette p = m_labelId->palette();
    p.setColor(QPalette::WindowText, Qt::white);
    m_labelId->setPalette(p);
}

void CrewMemberWidget::unselect()
{
    QPalette p = m_labelId->palette();
    p.setColor(QPalette::WindowText, Qt::black);
    m_labelId->setPalette(p);
}

void CrewMemberWidget::mousePressEvent(QMouseEvent* evt)
{
    Q_UNUSED(evt);
    select();
    emit memberSelection(m_labelId->text().toStdString());
}
