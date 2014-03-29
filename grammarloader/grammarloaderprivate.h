#ifndef GRAMMARLOADERPRIVATE_H
#define GRAMMARLOADERPRIVATE_H

#include <QVector>
#include <QStringList>
class Rule;

class GrammarLoaderPrivate
{
private:
    Q_DISABLE_COPY(GrammarLoaderPrivate)
public:
    GrammarLoaderPrivate();
    ~GrammarLoaderPrivate();

    QStringList unterminalSymbols;
    QStringList terminalSymbols;
    QVector <Rule*> rules;
    QStringList startWords;
    bool isValid;
};

#endif // GRAMMARLOADERPRIVATE_H
