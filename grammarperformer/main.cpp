#include <QCoreApplication>
#include <QDebug>

#include "grammarperformer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GrammarPerformer g;

    // g.readGrammar("rules.txt");          // Read from text file
    g.readGrammar("://data/rules.json");    // Read from resources file

    g.beginGenerate(5);
    while(g.isNextWord())
    {
        QString generated = g.nextWord();
        qDebug() << generated;
        if(generated.isEmpty())
            continue;
    }

    return a.exec();
}
