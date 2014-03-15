#ifndef RULESLOADER_H
#define RULESLOADER_H

#include <QStringList>

class Rule;

class GrammarLoader
{
public:
    GrammarLoader() {}
    GrammarLoader(const QString& _filename) {parceGrammar(_filename);}

    virtual void parceGrammar(const QString& _filename) = 0;

    virtual QStringList unterminalSymbols() const = 0;
    virtual QStringList terminalSymbols() const = 0;
    virtual QVector <Rule*> rules() const = 0;
    virtual QStringList startWords() const = 0;

    virtual bool isValid() const = 0;
};

#endif // GrammarLoader_H
