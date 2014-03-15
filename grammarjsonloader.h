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
    QStringList unterminalSymbols() const;
    QStringList terminalSymbols() const;
    QVector <Rule*> rules() const;
    QStringList startWords() const;

    virtual bool isValid() const;

private:
    bool m_isValid;
    QStringList m_unterminalSymbols;
    QStringList m_terminalSymbols;
    QVector <Rule*> m_rules;
    QStringList m_startWords;
};

#endif // GRAMMARJSONLOADER_H
