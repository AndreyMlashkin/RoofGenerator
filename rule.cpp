#include "rule.h"

int indexOfCharLessThenNull(const Word& _word)
{
    int ind = 0;
    foreach(QChar ch, _word)
    {
        ++ind;
        if(ch < 0)
            return ind;
    }
    return -1;
}

Rule::Rule(const Word& _from, const Word& _to)
    : m_leftSide(_from),
      m_rightSide(_to),
      m_unterminalIndex(indexOfCharLessThenNull(_from)),
      m_isValid(m_unterminalIndex >= 0)
{}

bool Rule::isValid() const
{
    return m_isValid;
}
