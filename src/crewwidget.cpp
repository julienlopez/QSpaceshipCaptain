#include "crewwidget.hpp"
#include "crewmemberwidget.hpp"
#include <ship/crewmember.hpp>

#include <cassert>

#include <QVBoxLayout>
#include <QLabel>

CrewWidget::CrewWidget(QWidget *parent) :
    QWidget(parent)
{
    m_currentSelection = 0;
    setMinimumWidth(200);
    m_layout = new QVBoxLayout;
    setLayout(m_layout);
}

void CrewWidget::addMember(const CrewMember &cm)
{
    m_layout->removeItem(m_layout->itemAt(m_layout->count()-1));
    CrewMemberWidget* cmw = new CrewMemberWidget(cm);
    connect(cmw, SIGNAL(memberSelection(std::string)), this, SIGNAL(memberSelection(std::string)));
    connect(cmw, SIGNAL(memberSelection(std::string)), this, SLOT(onCrewWidgetClicked(std::string)));
    m_layout->addWidget(cmw);
    m_layout->addStretch();
}

void CrewWidget::removeMember(const CrewMember& cm)
{

}

void CrewWidget::selectMember(const CrewMember &cm)
{
    unselectMember();
    CrewMemberWidget* w = findWidgetByName(cm.name());
    if(!w) return;
    m_currentSelection = w;
    w->select();
}

void CrewWidget::unselectMember()
{
    if(!m_currentSelection) return;
    m_currentSelection->unselect();
    m_currentSelection = 0;
}

CrewMemberWidget* CrewWidget::findWidgetByName(const std::string& name)
{
    QString str = QString::fromStdString(name);
    for(int i = 0; i < m_layout->count()-1; i++)
    {
        CrewMemberWidget* cmw = qobject_cast<CrewMemberWidget*>(m_layout->itemAt(i)->widget());
        if(!cmw) continue;
        if(cmw->labelId()->text() == str) return cmw;
    }
    return 0;
}

void CrewWidget::onCrewWidgetClicked(const std::string& name)
{
    if(m_currentSelection) m_currentSelection->unselect();
    CrewMemberWidget* w = findWidgetByName(name);
    assert(w);
    m_currentSelection = w;
}
