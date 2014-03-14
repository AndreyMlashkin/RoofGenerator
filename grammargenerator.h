#ifndef GRAMMARGENERATOR_H
#define GRAMMARGENERATOR_H

#include <QString>
#include <QVector>

#include "generatorapi.h"
#include "rule.h"

class GrammarGenerator
{
public:
    GrammarGenerator();

    void readGrammar(const QString& _filename);
    void generate(int _depth);

    QString getWord(int _num, int _depth = -1) const; // -1 means doesnot matter.
    int wordCount(int _depth = -1) const;

private:
    void tryUseRule(const Rule& _rule, const Word& _word);

private:
    int m_unterminalCount;
    int m_terminalCount;

    QVector<Rule*> m_rules;

};

#endif // GRAMMARGENERATOR_H
