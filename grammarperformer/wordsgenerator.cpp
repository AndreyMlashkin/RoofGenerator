#include <QDebug>
#include <QThread>

#include "wordsgenerator.h"
#include "grammarloader/grammarloader.h"
#include "rule.h"

WordsGenerator::WordsGenerator(GrammarLoader* _loader) :
    QObject(),
    m_isFinished(false),
    m_maxLevel(-1),
    m_level(0),
    m_loader(_loader->clone()),
    m_generatedWords()
{}

void WordsGenerator::begin()
{
    begin(m_level);
}

void WordsGenerator::begin(int _level)
{
    m_maxLevel = _level;
    m_generatedWords.resize(_level + 1);
    foreach (Word w, m_loader->startWords())
        generate(0, w);

    m_isFinished = true;
}

void WordsGenerator::setLevel(int _level)
{
    m_level = _level;
}

bool WordsGenerator::isValid() const
{
    if(m_loader && m_level > 0)
        if(m_loader->isValid())
            return true;

    return false;
}

const QVector<QSet<Word> > WordsGenerator::generatedWords() const
{
    return m_generatedWords;
}

bool WordsGenerator::isFinished() const
{
    return m_isFinished;
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
