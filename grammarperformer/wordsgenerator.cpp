#include <QDebug>
#include <QMutex>

#include "wordsgenerator.h"
#include "grammarloader/grammarloader.h"
#include "rule.h"

WordsGenerator::WordsGenerator(GrammarLoader* _loader, QMutex& _mutex) :
    QObject(),
    isFinished(false),
    m_maxLevel(-1),
    m_loader(_loader->clone()),
    m_generatedWords(),
    m_mutex(_mutex)
{}

void WordsGenerator::begin(int _level)
{
    m_maxLevel = _level;
    m_generatedWords.resize(_level + 1);
    foreach (Word w, m_loader->startWords())
        generate(0, w);

    emit finished();
}

bool WordsGenerator::isValid() const
{
    if(m_loader)
        if(m_loader->isValid())
            return true;

    return false;
}

const QVector<QSet<Word> > WordsGenerator::generatedWords() const
{
    return m_generatedWords;
}

void WordsGenerator::generate(int _level, const Word &_word)
{
    if(_level == m_maxLevel)
        return;

    foreach(Rule* rule, m_loader->rules())
    {
       QVector<Word> generated = rule->apply(_word);

       foreach (Word w, generated)
       {
           m_generatedWords[_level] << w;
           generate(_level+1, w);
       }
    }
}
