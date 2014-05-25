#include <QApplication>
#include <QTest>
#include "mainwindow.h"

#include "tests/testgrammar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTest::qExec(new TestGrammar, argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
