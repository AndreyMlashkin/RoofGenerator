#include "grammarloader.h"

#include "../generatorapi.h"
#include "grammarloaderprivate.h"

GrammarLoader::GrammarLoader()
    : p(new GrammarLoaderPrivate())
{}

GrammarLoader::~GrammarLoader()
{
    delete p;
}

QStringList GrammarLoader::unterminalSymbols() const
{
    return p->unterminalSymbols;
}

QStringList GrammarLoader::terminalSymbols() const
{
    return p->terminalSymbols;
}

const QVector<Rule *> GrammarLoader::rules() const
{
    return p->rules;
}

QStringList GrammarLoader::startWords() const
{
    return p->startWords;
}

bool GrammarLoader::isValid() const
{
    return p->isValid;
}
