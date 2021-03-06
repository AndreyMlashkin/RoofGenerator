#ifndef GRAMMARJSONLOADER_H
#define GRAMMARJSONLOADER_H

#include "grammarloader.h"

class GrammarJsonLoader : public GrammarLoader
{
public:
    GrammarJsonLoader();
    GrammarLoader* clone();

    void parceGrammar(const QString& _filename);
};

#endif // GRAMMARJSONLOADER_H
