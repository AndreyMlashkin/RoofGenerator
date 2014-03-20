#include <QDebug>
#include "rule.h"

Rule::Rule(const Word& _from, const Word& _to)
    : m_leftSide(_from),
      m_rightSide(_to),
      m_isValid(!m_leftSide.isEmpty())
{}

bool Rule::isValid() const
{
    return m_isValid;
}

inline int findNextInclusion(const Word& _word, const QString& _subStr, int _fromPos = 0)
{
    for(int i = _fromPos; i < _word.size(); i++)
    {
        int j = 0;
        while(_word[i+j] == _subStr[j])
        {
            j++;
            bool isOutOfLimit = (i+j >= _word.size()) || (j >= _subStr.size());
            if(isOutOfLimit)
                break;
        }

        if(j == _subStr.size())
            return i;
    }
    return -1;
}

QVector<Word> Rule::apply(const Word& _source) const
{
   int ind = 0;
   QVector<Word> generated;

   while((ind = findNextInclusion(_source, m_leftSide, ind)) != -1)
   {
       QString tmp = _source;
       tmp.replace(ind, m_leftSide.count(), m_rightSide);
       generated << tmp;
       ind++;
   }
   return generated;
}
