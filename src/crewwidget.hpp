#ifndef CREWWIDGET_HPP
#define CREWWIDGET_HPP

#include <QWidget>

class CrewMember;
class CrewMemberWidget;

class QVBoxLayout;

class CrewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CrewWidget(QWidget *parent = 0);
    
signals:
    void memberSelection(const std::string& name);

public slots:
    void addMember(const CrewMember& cm);
    void removeMember(const CrewMember& cm);
    void selectMember(const CrewMember& cm);
    void unselectMember();

private:
    QVBoxLayout* m_layout;
    CrewMemberWidget* m_currentSelection;

    CrewMemberWidget* findWidgetByName(const std::string& name);

private slots:
    void onCrewWidgetClicked(const std::string& name);
};

#endif // CREWWIDGET_HPP
