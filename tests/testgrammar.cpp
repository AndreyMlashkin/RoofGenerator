#include <QFile>
#include <QTest>

#include <QTextStream>

#include "testgrammar.h"
#include "grammarperformer/grammarloader/grammarnativeloader.h"

TestGrammar::TestGrammar(QObject *_parent) :
    QObject(_parent)
{
}

void TestGrammar::testLoader()
{
    QString filename("nativegrammartest.txt");
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QFAIL("Can't create/open file for test case!");
        return;
    }

    QTextStream out(&file);

    out << "N = {a}"    << endl <<
           "T = {0 1}"  << endl <<
           "S = {a}"    << endl <<
           "R ="        << endl <<
           "{"          << endl <<
           "a -> 0"     << endl <<
           "a -> 1"     << endl <<
           "a -> aa"    << endl <<
           "}";

    file.close();

    GrammarNativeLoader loader;

    loader.parceGrammar(filename);

    QCOMPARE(loader.startWords(), QStringList("a"));
}
