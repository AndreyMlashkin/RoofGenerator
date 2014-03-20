#ifndef GRAMMARJSONLOADER_H
#define GRAMMARJSONLOADER_H

#include <QStringList>
#include <QVector>
#include "grammarloader.h"

class GrammarJsonLoader : public GrammarLoader
{
public:
    GrammarJsonLoader();
    void parceGrammar(const QString& _filename);
};

#endif // GRAMMARJSONLOADER_H
