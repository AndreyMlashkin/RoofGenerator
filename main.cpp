#include <QDebug>
#include <QApplication>
#include <QFile>

#include "grammarperformer/grammarperformer.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile File("style.qss");
    if(!File.open(QFile::ReadOnly)){
        File.setFileName(":/style.qss");
        File.open(QFile::ReadOnly);
    }
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);

    MainWindow w;
    w.show();

    return a.exec();
}
