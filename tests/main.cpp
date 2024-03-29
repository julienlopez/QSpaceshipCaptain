#include <QTest>

#include "teststringlist.hpp"
#include "testroom.hpp"
#include "testjson.hpp"
#include "testpathinghelper.hpp"

int main(int argc, char *argv[])
{
    TestStringList test1;
    QTest::qExec(&test1, argc, argv);

    TestRoom test2;
    QTest::qExec(&test2, argc, argv);

    TestJSon test3;
    QTest::qExec(&test3, argc, argv);

    TestPathingHelper test4;
    QTest::qExec(&test4, argc, argv);
    
    return EXIT_SUCCESS;
}
