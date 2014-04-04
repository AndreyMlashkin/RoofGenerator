#include <QDebug>
#include <QApplication>

#include "grammarperformer/grammarperformer.h"
#include "roof.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GrammarPerformer g;
   // g.readGrammar("rules.txt");

    g.readGrammar("://data/rules.json");
    qDebug() << g.isValid();

    g.beginGenerate(5);

    while(g.isNextWord())
    {
        QString generated = g.nextWord();
        qDebug() << generated;
        if(generated.isEmpty())
            continue;
        roof *r = new roof;
        r->show();
        r->paintRoof(generated);
    }
    return a.exec();
}
