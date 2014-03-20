#ifndef RULESREADER_H
#define RULESREADER_H

#include "grammarloader.h"

class Rule;

class GrammarNativeLoader : public GrammarLoader
{
public:
    GrammarNativeLoader();
    void parceGrammar(const QString& _filename);

private:
    bool m_untermParsed;
    bool m_rulesParsed;
    bool m_terminalParsed;
    bool m_startWordParsed;
};

#endif // RULESREADER_H
