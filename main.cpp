#include <QDebug>
#include <QCoreApplication>

#include "grammargenerator.h"

#include "grammarnativeloader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

// ------Для теста------------------
    GrammarLoader* loader = new GrammarNativeLoader();
    loader->parceGrammar("rules.txt");

    qDebug() << loader->isValid();
    qDebug() << loader->rules();
    qDebug() << loader->startWord();
    qDebug() << loader->terminalSymbols();
    qDebug() << loader->unterminalSymbols();
// ------------------------


    GrammarGenerator g;
    g.readGrammar("roofGrammar.txt");
    g.generate(5);

    for(int i = 0; i < g.wordCount(); i++)
        qDebug() << g.getWord(i);


    return a.exec();
}
