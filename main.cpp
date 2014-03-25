#include <QDebug>
#include <QApplication>

#include "grammargenerator.h"
#include "roof.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GrammarGenerator g;
//    g.readGrammar("rules.txt");

    g.readGrammar("://data/rules.json");
    qDebug() << g.isValid();

    g.generate(5);
    g.generate(5);
    g.generate(5);
    qDebug() << g.wordCount();

    for(int i = 0; i < g.wordCount(); i++)
    {
        QString generated = g.getWord(i);
        qDebug() << generated;
        if(generated.isEmpty())
            continue;
        roof *r = new roof;
        r->show();
        r->paintRoof(generated);
    }
    return a.exec();
}
