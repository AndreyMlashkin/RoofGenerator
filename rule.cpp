#include <QDebug>
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
            return i+j - 1;
    }
    return -1;
}

QVector<Word> Rule::apply(const Word& _source) const
{
   int ind = 0;
   QVector<Word> generated;

   while((ind = findNextInclusion(_source, m_leftSide, ind)) != -1)
   {
       static int count = 0;
       qDebug() << count++;
       QString tmp = _source;
       //tmp.resize(ind + m_leftSide.count() + 1);
       tmp.replace(ind, m_leftSide.count(), m_rightSide);
       generated << tmp;
       ind++;
   }
   return generated;
}
