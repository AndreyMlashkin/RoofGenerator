#include <QDebug>

#include "grammargenerator.h"
#include "grammarjsonloader.h"
#include "grammarnativeloader.h"

GrammarGenerator::GrammarGenerator()
{
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

    m_loader = getLoader(type);
    m_loader->parceGrammar(_filename);
}

void GrammarGenerator::generate(int _depth)
{

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
