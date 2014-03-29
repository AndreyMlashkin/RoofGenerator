#ifndef GRAMMARLOADERPRIVATE_H
#define GRAMMARLOADERPRIVATE_H

#include <QVector>
#include <QStringList>
class Rule;

class GrammarLoaderPrivate
{
public:
    GrammarLoaderPrivate();
    GrammarLoaderPrivate(const GrammarLoaderPrivate& _loader);

    ~GrammarLoaderPrivate();

    QStringList unterminalSymbols;
    QStringList terminalSymbols;
    QVector <Rule*> rules;
    QStringList startWords;
    bool isValid;
};

#endif // GRAMMARLOADERPRIVATE_H
