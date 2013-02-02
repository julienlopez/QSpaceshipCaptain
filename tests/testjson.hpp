#ifndef TESTJSON_HPP
#define TESTJSON_HPP

#include <QObject>

class TestJSon : public QObject
{
    Q_OBJECT

public:
    TestJSon(QObject *parent = 0);
    
private slots:
    /**
      * \brief test json splitting mehtod, with a comma in a list of values
      */
    void testSplit1();
    /**
      * \brief test json splitting mehtod, with a comma in an object description
      */
    void testSplit2();
    /**
      * \brief test json splitting mehtod, with a comma in a string
      */
    void testSplit3();
    /**
      * \brief test json splitting mehtod, with a string before the splitting character
      */
    void testSplit4();
};

#endif // TESTJSON_HPP
