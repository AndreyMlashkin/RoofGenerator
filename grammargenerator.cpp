#include <QDebug>

#include "grammargenerator.h"
#include "grammarjsonloader.h"
#include "grammarnativeloader.h"
#include "rule.h"

GrammarGenerator::GrammarGenerator()
    : m_loader(NULL)
{
}

GrammarGenerator::~GrammarGenerator()
{
    delete m_loader;
}

void GrammarGenerator::readGrammar(const QString& _filename)
{
    LoaderType type = LoaderType(-1);
    if(_filename.contains("txt")) // regexp requied...
        type = Native;
    else if(_filename.contains("json")) //.*\\.json$
        type = Json;
    else
        qDebug() << "Invalid file type! " << Q_FUNC_INFO;

    delete m_loader;
    m_loader = getLoader(type);
    m_loader->parceGrammar(_filename);
}

void GrammarGenerator::generate(int _depth)
{
    m_generatedWords.resize(_depth + 1);
    foreach(QString s, m_loader->startWords())
        m_generatedWords[0] << s;

    for(int i = 0; i < _depth; i++)
    {
        foreach(QString s, m_generatedWords[i])
        {
            foreach(Rule* rule, m_loader->rules())
            {
               m_generatedWords[i+1] += rule->apply(s);
            }
        }

    }
}

QString GrammarGenerator::getWord(int _num, int _depth) const
{
    return 0;
}

int GrammarGenerator::wordCount(int _depth) const
{
    return 0;
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
