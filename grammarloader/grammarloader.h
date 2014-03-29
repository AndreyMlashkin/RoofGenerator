#ifndef RULESLOADER_H
#define RULESLOADER_H

#include <QStringList>
#include <QVector>

class Rule;
class GrammarLoaderPrivate;

class GrammarLoader
{
public:
    GrammarLoader();
    virtual ~GrammarLoader();

    virtual void parceGrammar(const QString&) = 0;

    QStringList unterminalSymbols() const;
    QStringList terminalSymbols() const;
    QVector <Rule*> rules() const;
    QStringList startWords() const;

    bool isValid() const;

protected:
    GrammarLoaderPrivate* p;
};

#endif // GrammarLoader_H
