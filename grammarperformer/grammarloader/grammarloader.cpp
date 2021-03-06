#include "grammarloader.h"

#include "../generatorapi.h"
#include "grammarloaderprivate.h"

GrammarLoader::GrammarLoader()
    : p(new GrammarLoaderPrivate())
{}

GrammarLoader& GrammarLoader::operator =(const GrammarLoader& _loader)
{
    if(&_loader == this)
        return *this;

    delete p;
    p = new GrammarLoaderPrivate(*_loader.p);
    return *this;
}

GrammarLoader::~GrammarLoader()
{
    delete p;
}

void GrammarLoader::setStartWords(const QStringList& _words)
{
    p->startWords = _words;
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
