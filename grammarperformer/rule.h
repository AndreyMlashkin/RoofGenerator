#ifndef RULE_H
#define RULE_H

#include "QVector"
#include "generatorapi.h"

class Rule
{
public:
    Rule(const Word& _from, const Word& _to);

    bool isValid() const;
    QVector<Word> apply(const Word& _source) const;

private:
    const Word m_leftSide;
    const Word m_rightSide;
    bool m_isValid;
};

#endif // RULE_H
