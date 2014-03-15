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
    QStringList startWords() const;

    bool isValid() const;

private:
    QStringList m_unterminalSymbols;
    QStringList m_terminalSymbols;
    QVector <Rule*> m_rules;
    QStringList m_startWords;

    bool m_untermParsed;
    bool m_rulesParsed;
    bool m_terminalParsed;
    bool m_startWordParsed;
};

#endif // RULESREADER_H
