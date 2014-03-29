#include <QDebug>
#include <QApplication>

#include "grammargenerator.h"
#include "roof.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GrammarGenerator g;
   // g.readGrammar("rules.txt");

    g.readGrammar("://data/rules.json");
    qDebug() << g.isValid();

    int i = 0;
    g.beginGenerate(6);
    while(g.isNextWord())
    {
        i++;
        QString generated = g.nextWord();
        qDebug() << generated;
        if(generated.isEmpty())
            continue;
//        roof *r = new roof;
//        r->show();
//        r->paintRoof(generated);
    }
    qDebug() << i;
    return a.exec();
}
