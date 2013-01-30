#include <QTest>

#include "teststringlist.hpp"
#include "testroom.hpp"
#include "testjson.hpp"

int main(int argc, char *argv[])
{
    TestStringList test1;
    QTest::qExec(&test1, argc, argv);

    TestRoom test2;
    QTest::qExec(&test2, argc, argv);

    TestJSon test3;
    QTest::qExec(&test3, argc, argv);
    
    return EXIT_SUCCESS;
}
