#include <QDebug>

#include "grammargenerator.h"
#include "grammarloader/grammarjsonloader.h"
#include "grammarloader/grammarnativeloader.h"
#include "rule.h"

GrammarGenerator::GrammarGenerator()
    : m_loader(NULL),
      m_currentUpdateVer(0),
      m_cacheVer(-1)
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

void GrammarGenerator::generate(int _depth)
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

void GrammarGenerator::clear()
{
    m_terminalWords.clear();
    m_unterminalWords.clear();
}

QString GrammarGenerator::getWord(int _num, int _level) const
{
    if(_level == -1)
    {
        if(m_currentUpdateVer != m_cacheVer)
            updateCache();
        return m_cachedWords[_num];
    }

    return m_terminalWords[_level].values()[_num];
}

int GrammarGenerator::wordCount(int _level) const
{
    if(_level != -1)
        return m_terminalWords[_level].size();

    if(m_currentUpdateVer != m_cacheVer)
        updateCache();
    return m_cachedWords.size();
}

bool GrammarGenerator::isValid() const
{
    if(m_loader)
        if(m_loader->isValid())
            return true;

    return false;
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

void GrammarGenerator::updateCache() const
{
    QSet<Word> cluster;
    foreach(QSet<Word> set, m_terminalWords)
        cluster.unite(set);

    m_cachedWords.clear();
    foreach(Word w, cluster)
        m_cachedWords << w;

    m_cacheVer = m_currentUpdateVer;
}
