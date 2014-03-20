#include "grammarloaderprivate.h"
#include "rule.h"

GrammarLoaderPrivate::GrammarLoaderPrivate()
    : isValid(false)
{}

GrammarLoaderPrivate::~GrammarLoaderPrivate()
{
    foreach(Rule* r, rules)
        delete r;
}
