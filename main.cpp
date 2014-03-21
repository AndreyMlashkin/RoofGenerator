#include <QDebug>
#include <QApplication>

#include "grammargenerator.h"
#include "roof.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    roof *r = new roof;
    r->show();
    r->paintRoof("/\\");
/*    GrammarGenerator g;
    //g.readGrammar("rules.txt");

    g.readGrammar("://data/rules.json");
    qDebug() << g.isValid();

    g.generate(3);

    for(int i = 0; i < g.wordCount(); i++)
        qDebug() << g.getWord(i);*/

    return a.exec();
}
