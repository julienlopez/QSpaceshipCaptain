#include "testjson.hpp"
#include <utils/json.hpp>
#include <utils/stringlist.hpp>

#include <QTest>

TestJSon::TestJSon(QObject *parent) :
    QObject(parent)
{}

void TestJSon::testSplit1()
{
    std::string str = "hello, yes : [\"no\", \"I don't think so.\"]";
    StringList strl = JSon::split(str, ',');
    QCOMPARE(strl.size(), (size_t)2);
    QCOMPARE(strl.front(), std::string("hello"));
    QCOMPARE(strl.back(), std::string(" yes : [\"no\", \"I don't think so.\"]"));
}

void TestJSon::testSplit2()
{
    std::string str = "hello, yes : { \"value\": \"no\", \"str\" : \"I don't think so.\"}";
    StringList strl = JSon::split(str, ',');
    QCOMPARE(strl.size(), (size_t)2);
    QCOMPARE(strl.front(), std::string("hello"));
    QCOMPARE(strl.back(), std::string(" yes : { \"value\": \"no\", \"str\" : \"I don't think so.\"}"));
}

void TestJSon::testSplit3()
{
    std::string str = "hello, yes : \"no, I don't think so.\"";
    StringList strl = JSon::split(str, ',');
    QCOMPARE(strl.size(), (size_t)2);
    QCOMPARE(strl.front(), std::string("hello"));
    QCOMPARE(strl.back(), std::string(" yes : \"no, I don't think so.\""));
}

void TestJSon::testSplit4()
{
    std::string str = "\"hello\", yes : \"no, I don't think so.\"";
    StringList strl = JSon::split(str, ',');
    QCOMPARE(strl.size(), (size_t)2);
    QCOMPARE(strl.front(), std::string("\"hello\""));
    QCOMPARE(strl.back(), std::string(" yes : \"no, I don't think so.\""));
}
