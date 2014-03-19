#include <QDebug>
#include <QCoreApplication>

#include "grammargenerator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GrammarGenerator g;
    g.readGrammar("rules.txt");
    qDebug() << g.isValid();

//    g.readGrammar("://data/rules.json");
//    qDebug() << g.isValid();

    g.generate(3);

    for(int i = 0; i < g.wordCount(); i++)
        qDebug() << g.getWord(i);

    return a.exec();
}
