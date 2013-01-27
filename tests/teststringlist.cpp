#include "teststringlist.hpp"

#include <utils/stringlist.hpp>

#include <QTest>

TestStringList::TestStringList()
{
}

void TestStringList::test_join1()
{
    StringList strl;
    std::string s1 = "Yeah";
    strl << s1;
    QCOMPARE(strl.join(";"), s1);
}

void TestStringList::test_join2()
{
    StringList strl;
    std::string s1 = "Yeah";
    std::string s2 = "Nope";
    strl << s1 << s2;
    QCOMPARE(strl.join(";"), s1+";"+s2);
}

void TestStringList::test_join3()
{
    StringList strl;
    std::string s1 = "Yeah";
    std::string s2 = "Nope";
    std::string s3 = "I guess so!";
    strl << s1 << s2 << s3;
    QCOMPARE(strl.join(";"), s1+";"+s2+";"+s3);
}

void TestStringList::test_splitSimple1()
{
    std::string str = "Bim bam boum";
    StringList strl = StringList::split(str, ",");
    QCOMPARE(strl.size(), (size_t)1);
}

void TestStringList::test_splitSimple2()
{
    std::string str = "Bim bam boum, top";
    StringList strl = StringList::split(str, ",");
    QCOMPARE(strl.size(), (size_t)2);
    QCOMPARE(strl.front(), std::string("Bim bam boum"));
    QCOMPARE(strl.back(), std::string(" top"));
}

void TestStringList::test_splitSimple3()
{
    std::string str = "Bim bam boum, top,Hello everyone";
    StringList strl = StringList::split(str, ",");
    QCOMPARE(strl.size(), (size_t)3);
    QCOMPARE(strl.front(), std::string("Bim bam boum"));
    QCOMPARE(*(++strl.begin()), std::string(" top"));
    QCOMPARE(strl.back(), std::string("Hello everyone"));
}
