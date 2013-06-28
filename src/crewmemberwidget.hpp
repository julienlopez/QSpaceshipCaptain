#ifndef CREWMEMBERWIDGET_HPP
#define CREWMEMBERWIDGET_HPP

#include <QWidget>

class CrewMember;

class QLabel;

class CrewMemberWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CrewMemberWidget(const CrewMember& cm, QWidget *parent = 0);

    QLabel* labelId() const;

    void select();
    void unselect();

protected:
    virtual void mousePressEvent(QMouseEvent* evt);
    
signals:
    void memberSelection(const std::string& name);
    
public slots:

private:
    QLabel* m_labelId;
    
};

#endif // CREWMEMBERWIDGET_HPP
