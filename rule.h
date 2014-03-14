#ifndef RULE_H
#define RULE_H

#include "generatorapi.h"

class Rule
{
public:
    Rule(const Word& _from, const Word& _to);

    bool isValid() const;
    QList<Word*> apply(const Word& _source) const;

private:
    bool m_isValid;

    const Word m_leftSide;
    const int m_unterminalIndex;
    const Word m_rightSide;
};

#endif // RULE_H
