#ifndef RULESLOADER_H
#define RULESLOADER_H

#include <QVector>
#include <QStringList>
#include "generatorapi.h"

class Rule;

class RulesLoader
{
public:
    RulesLoader() {}
    virtual void parceGrammar(const QString& _filename) = 0;

    virtual QStringList unterminalSymbols() const = 0;
    virtual QStringList terminalSymbols() const = 0;
    virtual QVector<Rule*> rules() const = 0;
    virtual Word startWord() const = 0;

    virtual bool isValid() const = 0;
};

#endif // RULESLOADER_H
