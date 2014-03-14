#ifndef RULESREADER_H
#define RULESREADER_H

#include "grammarloader.h"

class Rule;

class GrammarNativeLoader : public GrammarLoader
{
public:
    GrammarNativeLoader();
    void parceGrammar(const QString& _filename);

    QStringList unterminalSymbols() const;
    QStringList terminalSymbols() const;
    QVector<Rule*> rules() const;
    Word startWord() const;

    bool isValid() const;

private:
    bool m_isValid;
    QStringList m_unterminalSymbols;
    QStringList m_terminalSymbols;
    QVector<Rule*> m_rules;
    Word m_startWord;
};

#endif // RULESREADER_H