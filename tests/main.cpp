#include <QTest>

#include "teststringlist.hpp"

int main(int argc, char *argv[])
{
    TestStringList test1;
    QTest::qExec(&test1, argc, argv);
    
    return EXIT_SUCCESS;
}
