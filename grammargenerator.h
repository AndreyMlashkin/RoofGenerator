#ifndef GRAMMARGENERATOR_H
#define GRAMMARGENERATOR_H

#include <QString>
#include <QVector>
#include <QSet>

#include "generatorapi.h"

class GrammarLoader;

class GrammarGenerator
{
public:
    GrammarGenerator();
    ~GrammarGenerator();

    void readGrammar(const QString& _filename);
    void beginGenerate(int _level);
    bool isValid() const;

    void reset();
    bool isNextWord();
    Word nextWord();

private:
    void generate(int _level, const Word& _word);

    enum LoaderType {Json, Native};
    GrammarLoader* getLoader(LoaderType _type);

    void separateTemAndUnterm(const QVector<Word>& _common, QSet<Word>& _terminal, QSet<Word>& _unterminal);

    bool isTerminal(const Word& _word);


//    void updateCache() const;

private:
    int m_maxLevel;

    QVector <QSet<Word> > m_unterminalWords; // By levels.
    QVector <QSet<Word> > m_terminalWords;

    int m_currentWordNum;

//    mutable int m_cacheVer;
//    mutable QStringList m_cachedWords;

    GrammarLoader* m_loader;
};

#endif // GRAMMARGENERATOR_H
