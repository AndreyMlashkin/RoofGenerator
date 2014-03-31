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

    g.beginGenerate(6);

    int count = 0;
    while(g.isNextWord())
    {
        QString generated = g.nextWord();
        qDebug() << generated;
        if(generated.isEmpty())
            continue;
        roof *r = new roof;
        r->show();
        r->paintRoof(generated);
        ++count;
    }
    qDebug() << count << " words generated";
    return a.exec();
}
