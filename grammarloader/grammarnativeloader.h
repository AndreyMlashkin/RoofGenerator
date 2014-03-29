#ifndef RULESREADER_H
#define RULESREADER_H

#include "grammarloader.h"

class Rule;

class GrammarNativeLoader : public GrammarLoader
{
public:
    GrammarNativeLoader();
    void parceGrammar(const QString& _filename);
};

#endif // RULESREADER_H
