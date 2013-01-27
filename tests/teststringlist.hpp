#ifndef TESTSTRINGLIST_HPP
#define TESTSTRINGLIST_HPP

#include <QObject>

class TestStringList : public QObject
{
    Q_OBJECT

public:
    TestStringList();

private slots:
    void test_join1();
    void test_join2();
    void test_join3();

    void test_splitSimple1();
    void test_splitSimple2();
    void test_splitSimple3();
};

#endif // TESTSTRINGLIST_HPP
