#include <QDebug>

#include "grammargenerator.h"
#include "grammarloader/grammarjsonloader.h"
#include "grammarloader/grammarnativeloader.h"
#include "rule.h"
#include "wordsgenerator.h"

GrammarGenerator::GrammarGenerator()
    : m_loader(NULL),
      m_currentWordNum(0),
      m_generator(NULL)
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
        qDebug() << "Error opening file.";
    }
    delete m_loader;
    m_loader = getLoader(type);
    if(m_loader)
        m_loader->parceGrammar(_filename);
}

void GrammarGenerator::beginGenerate(int _level)
{
    m_unterminalWords.resize(_level + 1);
    m_terminalWords.resize  (_level + 1);
    m_maxLevel = _level;


    m_generator = new WordsGenerator(m_loader);

    connect(m_generator, SIGNAL(finished()), this, SLOT(generatorFinished()));
    m_generator->begin(_level);

    delete m_generator;
    m_generator = NULL;
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
    return m_currentWordNum < m_terminalWords[m_maxLevel-1].size();
}

Word GrammarGenerator::nextWord()
{
    ++m_currentWordNum;
    return m_terminalWords[m_maxLevel-1].toList()[m_currentWordNum-1];
}

void GrammarGenerator::generatorFinished()
{
    Q_ASSERT(m_generator);
    merge(m_generator->generatedWords());
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

void GrammarGenerator::merge(QVector<QSet<Word> > _words)
{
    int lvl = 0;
    foreach(QSet<Word> set, _words)
    {
        foreach(Word w, set)
        {
            if(isTerminal(w))
                m_terminalWords[lvl] << w;
            else
                m_unterminalWords[lvl] << w;
        }
        ++lvl;
    }

    QSet<Word> clusteredIncoming;
    foreach(QSet<Word> set, _words)
        clusteredIncoming += set;

    QSet<Word> newWords = m_clasteredTerminalWords.subtract(clusteredIncoming);

    foreach(Word w, newWords)
        m_orderedClasteredTerminalWords << w;
//    m_orderedClasteredTerminalWords  << newWords;

    m_clasteredTerminalWords += clusteredIncoming;
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
