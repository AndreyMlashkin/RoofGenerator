#include "grammarloaderprivate.h"
#include "../rule.h"

GrammarLoaderPrivate::GrammarLoaderPrivate()
    : isValid(false)
{}

GrammarLoaderPrivate::GrammarLoaderPrivate(const GrammarLoaderPrivate& _loader)
{
    unterminalSymbols = _loader.unterminalSymbols;
    terminalSymbols   = _loader.terminalSymbols;
    startWords        = _loader.startWords;
    isValid           = _loader.isValid;

    foreach(Rule* r, _loader.rules)
        rules << r;
}

GrammarLoaderPrivate::~GrammarLoaderPrivate()
{
    foreach(Rule* r, rules)
        delete r;
}
