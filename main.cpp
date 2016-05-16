#include "mainwindow.h"
#include <QApplication>
//#include "tests/tests.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    Tests tests;
//    QTest::qExec(&tests);
    w.show();

    return a.exec();
}
