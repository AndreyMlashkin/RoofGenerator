#ifndef GRAMMARLOADERPRIVATE_H
#define GRAMMARLOADERPRIVATE_H

#include <QVector>
#include <QStringList>
class Rule;

struct GrammarLoaderPrivate
{
    GrammarLoaderPrivate();
    ~GrammarLoaderPrivate();

    QStringList unterminalSymbols;
    QStringList terminalSymbols;
    QVector <Rule*> rules;
    QStringList startWords;
    bool isValid;
};

#endif // GRAMMARLOADERPRIVATE_H
