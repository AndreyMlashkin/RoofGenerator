#include <QDebug>

#include "grammargenerator.h"
#include "grammarloader/grammarjsonloader.h"
#include "grammarloader/grammarnativeloader.h"
#include "rule.h"

GrammarGenerator::GrammarGenerator()
    : m_loader(NULL),
      m_currentWordNum(0)
{}

GrammarGenerator::~GrammarGenerator()
{
    delete m_loader;
}

void GrammarGenerator::readGrammar(const QString& _filename)
{
    LoaderType type = LoaderType(-1);
    try
    {
        if(_filename.contains(QRegExp(".*\\.txt")))
            type = Native;
        else if(_filename.contains(QRegExp("\\.json$")))
            type = Json;
        else
            qDebug() << "Invalid file type! " << Q_FUNC_INFO;
    }
    catch(...)
    {
        qDebug() << "error opening file";
    }
    delete m_loader;
    m_loader = getLoader(type);
    if(m_loader)
        m_loader->parceGrammar(_filename);
}

void GrammarGenerator::beginGenerate(int _level)
{
    m_maxLevel = _level;
    m_unterminalWords.resize(_level + 1);
    m_terminalWords.resize  (_level + 1);
    foreach (Word w, m_loader->startWords())
        generate(0, w);
}

/*void GrammarGenerator::generateAll(int _depth)
{     
    ++m_currentUpdateVer;
    clear();
    if(!m_loader)
        return;

    m_unterminalWords.resize(_depth + 1);
    m_terminalWords.resize(_depth + 1);

    foreach(QString s, m_loader->startWords())
        m_unterminalWords[0] << s;

    for(int i = 0; i < _depth; i++)
    {
        foreach(QString s, m_unterminalWords[i])
        {
            foreach(Rule* rule, m_loader->rules())
            {
               QVector<Word> generated = rule->apply(s);
               separateTemAndUnterm(generated, m_terminalWords[i+1], m_unterminalWords[i+1]);
            }
        }
    }
}
*/

void GrammarGenerator::generate(int _level, const Word& _word)
{
    bool isTerm = isTerminal(_word);
    if(isTerm)
    {
        m_terminalWords[_level] << _word;
        return;
    }
    else
        m_unterminalWords[_level] << _word;


    if(_level == m_maxLevel)
        return;

    foreach(Rule* rule, m_loader->rules())
    {
       QVector<Word> generated = rule->apply(_word);
       foreach (Word w, generated)
            generate(_level+1, w);
    }
}

bool GrammarGenerator::isValid() const
{
    if(m_loader)
        if(m_loader->isValid())
            return true;

    return false;
}

void GrammarGenerator::reset()
{
    m_currentWordNum = 0;
}

bool GrammarGenerator::isNextWord()
{
    return m_currentWordNum < m_terminalWords[m_maxLevel].size();
}

Word GrammarGenerator::nextWord()
{
    m_currentWordNum++;
    return m_terminalWords[m_maxLevel].toList()[m_currentWordNum-1];
}

GrammarLoader *GrammarGenerator::getLoader(GrammarGenerator::LoaderType _type)
{
    if(_type == Json)
        return new GrammarJsonLoader();
    if(_type == Native)
        return new GrammarNativeLoader();
    else
        return NULL;
}

void GrammarGenerator::separateTemAndUnterm(const QVector<Word>& _common, QSet<Word>& _terminal, QSet<Word>& _unterminal)
{
    foreach(Word w, _common)
    {
        bool isTerminal = true;
        foreach(QString s, m_loader->unterminalSymbols())
        {
            if(w.contains(s))
            {
                _unterminal << w;
                isTerminal = false;
                break;
            }
        }
        if(isTerminal)
            _terminal << w;
    }
}

bool GrammarGenerator::isTerminal(const Word& _word)
{
    bool isTerminal = true;
    foreach(QString s, m_loader->unterminalSymbols())
    {
        if(_word.contains(s))
        {
            isTerminal = false;
            break;
        }
    }
    return isTerminal;
}
/*
void GrammarGenerator::updateCache() const
{
    QSet<Word> cluster;
    foreach(QSet<Word> set, m_terminalWords)
        cluster.unite(set);

    m_cachedWords.clear();
    foreach(Word w, cluster)
        m_cachedWords << w;

    m_cacheVer = m_currentWordNum;
}
*/
