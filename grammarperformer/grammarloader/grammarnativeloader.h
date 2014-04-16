#ifndef RULESREADER_H
#define RULESREADER_H

#include "grammarloader.h"

class Rule;

class GrammarNativeLoader : public GrammarLoader
{
public:
    GrammarNativeLoader();
    GrammarLoader* clone();

    void parceGrammar(const QString& _filename);
};

#endif // RULESREADER_H
