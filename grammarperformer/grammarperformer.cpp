#include <QDebug>

#include "grammarperformer.h"
#include "grammarloader/grammarjsonloader.h"
#include "grammarloader/grammarnativeloader.h"
#include "rule.h"
#include "wordsgenerator.h"

GrammarPerformer::GrammarPerformer()
    : m_maxLevel(-1),
      m_currentWordNum(0),
      m_loader(NULL),
      m_generator(NULL)
{}

GrammarPerformer::~GrammarPerformer()
{
    delete m_loader;
}

void GrammarPerformer::readGrammar(const QString& _filename)
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
        qDebug() << "Error opening file.";
    }
    delete m_loader;
    m_loader = getLoader(type);
    if(m_loader)
        m_loader->parceGrammar(_filename);
}

void GrammarPerformer::beginGenerate(int _level)
{
    reset();

    m_unterminalWords.resize(_level + 1);
    m_terminalWords.resize  (_level + 1);
    m_maxLevel = _level;

    m_generator = new WordsGenerator(m_loader);

    connect(m_generator, SIGNAL(finished()), this, SLOT(generatorFinished()));
    m_generator->begin(_level);

    delete m_generator;
    m_generator = NULL;
}

bool GrammarPerformer::isValid() const
{
    if(m_loader)
        if(m_loader->isValid())
            return true;

    return false;
}

void GrammarPerformer::reset()
{
    m_currentWordNum = 0;
    m_maxLevel = -1;
    m_unterminalWords.clear();
    m_terminalWords.clear();

    m_clasteredTerminalWords.clear();
    m_orderedClasteredTerminalWords.clear();
}

bool GrammarPerformer::isNextWord()
{
    return m_currentWordNum < m_orderedClasteredTerminalWords.size();
}

Word GrammarPerformer::nextWord()
{
    ++m_currentWordNum;
    return m_orderedClasteredTerminalWords[m_currentWordNum-1];
}

void GrammarPerformer::generatorFinished()
{
    Q_ASSERT(m_generator);
    merge(m_generator->generatedWords());
}

GrammarLoader *GrammarPerformer::getLoader(GrammarPerformer::LoaderType _type)
{
    if(_type == Json)
        return new GrammarJsonLoader();
    if(_type == Native)
        return new GrammarNativeLoader();
    else
        return NULL;
}

void GrammarPerformer::merge(QVector<QSet<Word> > _words)
{
    int lvl = 0;
    QSet<Word> clusteredIncoming;
    foreach(QSet<Word> set, _words)
    {
        foreach(Word w, set)
        {
            if(isTerminal(w))
            {
                m_terminalWords[lvl] << w;
                clusteredIncoming << w;
            }
            else
                m_unterminalWords[lvl] << w;
        }
        ++lvl;
    }

    QSet<Word> newWords = clusteredIncoming.subtract(m_clasteredTerminalWords);//.subtract(clusteredIncoming);

    foreach(Word w, newWords)
        m_orderedClasteredTerminalWords << w;

    m_clasteredTerminalWords += clusteredIncoming;
}

void GrammarPerformer::separateTemAndUnterm(const QVector<Word>& _common, QSet<Word>& _terminal, QSet<Word>& _unterminal)
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

bool GrammarPerformer::isTerminal(const Word& _word)
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